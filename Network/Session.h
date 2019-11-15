#pragma once

#include "Utility/Common.h"

namespace Network {

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(boost::asio::ip::tcp::socket socket);
    virtual ~Session();

    void Start();
    void Send(SharedPtr<std::string const> const& payload);

protected:
    void OnAccept(boost::beast::error_code ec);

    void DoRead();
    virtual void OnRead(boost::beast::error_code ec, std::size_t bytes_transferred);

    virtual bool OnHandle(const std::string& payload) = 0;
    virtual void OnDisconnected(boost::beast::error_code ec) = 0;

    void OnSend(SharedPtr<std::string const> const& payload);
    void OnWrite(boost::beast::error_code ec, std::size_t);

    void Close();

    boost::beast::websocket::stream<boost::beast::tcp_stream> websocket_;
    //boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::beast::flat_buffer buffer_;

    std::vector<SharedPtr<std::string const>> queue_;
};

} // Network
