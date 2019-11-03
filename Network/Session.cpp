#include "stdafx.h"
#include "Network/Session.h"

namespace Network {

static void Fail(boost::beast::error_code ec, char const* what) {
    if (ec == boost::asio::error::operation_aborted ||
        ec == boost::beast::websocket::error::closed) {
        return;
    }

    std::cerr << what << ": " << ec.message() << "\n";
}
  
Session::Session(boost::asio::ip::tcp::socket socket)
    : websocket_(std::move(socket)) {

}

Session::~Session() {
}

void Session::Start() {
    // Set suggested timeout settings for the websocket
    websocket_.set_option(
        boost::beast::websocket::stream_base::timeout::suggested(
            boost::beast::role_type::server));

    // Set a decorator to change the Server of the handshake
    websocket_.set_option(boost::beast::websocket::stream_base::decorator(
        [](boost::beast::websocket::response_type& res) {
        res.set(boost::beast::http::field::server,
            std::string(BOOST_BEAST_VERSION_STRING) +
            " websocket-server-async");
    }));

    // Accept the websocket handshake
    websocket_.async_accept(
        boost::beast::bind_front_handler(
            &Session::OnAccept,
            shared_from_this()
        )
    );
}

void Session::OnAccept(boost::beast::error_code ec) {
    if (ec) {
        //return HandleFailure(ec, "accept");
    }
    // Read a message
    DoRead();
}

void Session::DoRead() {
    // Read a message into our buffer
    websocket_.async_read(
        buffer_,
        boost::beast::bind_front_handler(
            &Session::OnRead,
            shared_from_this()
        )
    );
}

void Session::OnRead(
    boost::beast::error_code ec,
    std::size_t bytes_transferred
) {
    /*
    if (ec) {
        return Fail(ec, "read");
    }
    */


    // Send to all connections
    //state_->send(beast::buffers_to_string(buffer_.data()));

    //const auto payload = boost::beast::buffers_to_string(buffer_.data());
    

    // Clear the buffer
    buffer_.consume(buffer_.size());

    DoRead();
    // Read another message
    /*
    websocket_.async_read(
        buffer_,
        Beast::bind_front_handler(
            &Session::OnRead,
            shared_from_this()
        )
    );
    */
}

void Session::Send(SharedPtr<std::string const> const& payload)
{
    // Post our work to the strand, this ensures
    // that the members of `this` will not be
    // accessed concurrently.
    boost::asio::post(
        websocket_.get_executor(),
        boost::beast::bind_front_handler(
            &Session::OnSend,
            shared_from_this(),
            payload
        )
    );
}

void Session::OnSend(
    SharedPtr<std::string const> const& payload
) {
    // Always add to queue
    queue_.push_back(payload);

    // Are we already writing?
    if (queue_.size() > 1)
        return;

    // We are not currently writing, so send this immediately
    websocket_.async_write(
        boost::asio::buffer(*queue_.front()),
        boost::beast::bind_front_handler(
            &Session::OnWrite,
            shared_from_this()
        )
    );
}

void Session::OnWrite(boost::beast::error_code ec, std::size_t) {
    // Handle the error, if any
    if (ec) {
        return Fail(ec, "write");
    }

    // Remove the string from the queue
    queue_.erase(queue_.begin());
    /*
    std::cout << "queue size: " << queue_.size() << std::endl;
    if (queue_.size() > 1000) {
        Close();
    }
    */

    // Send the next message if any
    if (!queue_.empty()) {
        websocket_.async_write(
            boost::asio::buffer(*queue_.front()),
            boost::beast::bind_front_handler(
                &Session::OnWrite,
                shared_from_this()
            )
        );
    }
}

void Session::Close() {
    try {
        websocket_.close(boost::beast::websocket::close_reason());
    } catch (...) {
        std::cout << boost::current_exception_diagnostic_information() << std::endl;
    }
    /*
    catch (const boost::exception& e) {
        e.what();
    }
    */
}

} // Network


// https://github.com/boostorg/beast/blob/develop/example/websocket/server/chat-multi/websocket_session.cpp
// https://github.com/boostorg/beast/tree/develop/example/websocket/server/chat-multi
