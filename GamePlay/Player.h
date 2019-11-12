#pragma once

#include <memory>

namespace Server {
class GameSession;
}

namespace GamePlay {

class Message;
class Table;

class Player {
public:
    explicit Player(std::shared_ptr<Server::GameSession> session);
    virtual ~Player();

    virtual void OnEvent(const Message& msg) = 0;
private:

    std::weak_ptr<Server::GameSession> session_;
};

} // namespace GamePlay