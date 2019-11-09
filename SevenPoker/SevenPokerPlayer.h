#pragma once

#include "GamePlay/Player.h"

class SevenPokerTable;

namespace SevenPoker {

class SevenPokerPlayer : GamePlay::Player {
public:
    SevenPokerPlayer(SevenPokerTable& table, std::shared_ptr<Server::GameSession> session);
    virtual ~SevenPokerPlayer();

private:
    const SevenPokerTable& table_;
};

} // namespace SevenPoker