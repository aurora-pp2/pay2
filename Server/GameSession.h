#pragma once

#include "Network/Session.h"
#include "Utility/Common.h"

namespace Server {

class GameSession;

using HandlerCallback = std::function<bool(std::shared_ptr<GameSession>, const Payload&)>;

class GameSession : public Network::Session {
public:
    explicit GameSession(boost::asio::ip::tcp::socket socket);
    virtual ~GameSession();

    static bool RegisterHandler(int packet_id, HandlerCallback handler);

    void Send(const Payload& payload);

private:
    void OnRead(boost::beast::error_code ec, std::size_t bytes_transferred) override;
    bool OnHandle(const std::string& payload) override;

    
};

} // namespace Server
