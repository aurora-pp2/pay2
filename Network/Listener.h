#pragma once

namespace Network {
class Session;

class Listener : public std::enable_shared_from_this<Listener> {
public:
    Listener(
        boost::asio::io_context& io_context,
        boost::asio::ip::tcp::endpoint endpoint
    );

    // Start accepting incoming connections
    void Run();

private:
    void Fail(boost::beast::error_code ec, char const* what);
    //void Fail(boost::beast::error_code ec, char const* what);
    void OnAccept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);

    virtual void Accepted(tcp::socket socket) = 0;

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

} // namespace Network
