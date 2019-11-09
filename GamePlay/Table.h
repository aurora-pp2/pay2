#pragma once

#include <vector>
#include <mutex>

namespace Server {
class GameSession;
}

namespace GamePlay {

class Player;

class Table {
public:
    virtual ~Table() {}

    //virtual std::shared_ptr<GamePlay::Player> JoinPlayer(std::shared_ptr<Server::GameSession> session) = 0;
    //virtual std::vector<std::shared_ptr<GamePlay::Player>> players() const = 0;

protected:
    virtual bool is_available_seat() const = 0;

    //std::vector<std::shared_ptr<GamePlay::Player>> players_;
    //std::array<std::shared_ptr<GamePlay::Player>> players_;
    std::mutex mutex_;
};

} // namespace GamePlay