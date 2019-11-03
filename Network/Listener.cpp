#include "stdafx.h"
#include "Network/Listener.h"
#include "Network/Session.h"

namespace Network {

Listener::Listener(
    boost::asio::io_context& ioc,
    boost::asio::ip::tcp::endpoint endpoint
) : io_context_(ioc), acceptor_(ioc) {
    boost::beast::error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if (ec) {
        Fail(ec, "open");
        return;
    }

    // Allow address reuse
    acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
    if (ec) {
        Fail(ec, "set_option");
        return;
    }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if (ec) {
        Fail(ec, "bind");
        return;
    }

    // Start listening for connections
    acceptor_.listen(
        boost::asio::socket_base::max_listen_connections, ec);
    if (ec) {
        Fail(ec, "listen");
        return;
    }
}

void Listener::Fail(boost::beast::error_code ec, char const* what) {
    // Don't report on canceled operations
    if (ec == boost::asio::error::operation_aborted)
        return;
    std::cerr << what << ": " << ec.message() << "\n";
}


void Listener::Run() {
    acceptor_.async_accept(
        boost::asio::make_strand(io_context_),
        boost::beast::bind_front_handler(
            &Listener::OnAccept,
            shared_from_this()
        )
    );
}

void Listener::OnAccept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) {
    
    if (ec) {
        return Fail(ec, "accept");
    }
    
    Accepted(std::move(socket));
    /*
    std::make_shared<Session>(
        std::move(socket))->Start();
        */

    // The new connection gets its own strand
    acceptor_.async_accept(
        boost::asio::make_strand(io_context_),
        boost::beast::bind_front_handler(
            &Listener::OnAccept,
            shared_from_this()
        )
    );
}

} // namespace Network
