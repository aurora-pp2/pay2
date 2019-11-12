#pragma once

#include "Network/Session.h"
#include "Utility/Common.h"
#include <memory>

namespace GamePlay {
class Player;
} // namespace GamePlay

namespace Server {

class GameSession;

using HandlerCallback = std::function<bool(std::shared_ptr<GameSession>, const Payload&)>;

class GameSession : public Network::Session {
public:
    explicit GameSession(boost::asio::ip::tcp::socket socket);
    virtual ~GameSession();

    static bool RegisterHandler(int packet_id, HandlerCallback handler);

    void Send(const Payload& payload);

    std::shared_ptr<GamePlay::Player> player() const;
    void set_player(std::shared_ptr<GamePlay::Player> player);

    size_t uid() const;
    void set_uid(size_t uid);

private:
    void OnRead(boost::beast::error_code ec, std::size_t bytes_transferred) override;
    bool OnHandle(const std::string& payload) override;

    size_t uid_;
    
    std::weak_ptr<GamePlay::Player> player_;
    std::mutex mutex_;
};

} // namespace Server
