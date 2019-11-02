#pragma once

namespace Network {

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(tcp::socket socket);
    virtual ~Session();

    void Start();
    void Send(SharedPtr<std::string const> const& payload);
    

protected:
    void OnAccept(Beast::error_code ec);

    void DoRead();
    virtual void OnRead(Beast::error_code ec, std::size_t bytes_transferred);

    virtual bool OnHandle(const std::string& payload) = 0;

    void OnSend(SharedPtr<std::string const> const& payload);
    void OnWrite(Beast::error_code ec, std::size_t);

    void Close();

    WebSocket::stream<Beast::tcp_stream> websocket_;
    //boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    Beast::flat_buffer buffer_;

    std::vector<SharedPtr<std::string const>> queue_;
};

} // Network
