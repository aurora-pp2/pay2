#pragma once

#include <memory>

namespace Server {
class GameSession;
}

namespace GamePlay {

class Table;

class Player {
public:
    explicit Player(std::shared_ptr<Server::GameSession> session);
    virtual ~Player();

private:

    std::weak_ptr<Server::GameSession> session_;
};

} // namespace GamePlay