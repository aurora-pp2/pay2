#pragma once

#include "GamePlay/Table.h"

namespace Network {
class Session;
} // namespace Network

namespace Server {
class GameSession;
}

namespace SevenPoker {

class SevenPokerPlayer;

class Table {
public:
    static const size_t kMaxPlayer = 5;

    ~Table() {}
    std::shared_ptr<SevenPokerPlayer> JoinPlayer(std::shared_ptr<Server::GameSession> session);
    
protected:
    bool is_available_seat() const;

private:
    
    std::array<std::shared_ptr<SevenPokerPlayer>, kMaxPlayer> seats_ = { nullptr, };
};

}
