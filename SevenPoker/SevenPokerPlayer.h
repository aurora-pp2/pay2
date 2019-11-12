#pragma once

#include "GamePlay/Player.h"

namespace SevenPoker {

class Table;

class SevenPokerPlayer : public GamePlay::Player {
public:
    SevenPokerPlayer(Table& table, std::shared_ptr<Server::GameSession> session);
    virtual ~SevenPokerPlayer();

    void OnEvent(const GamePlay::Message& msg) override;

private:
    std::mutex mutex_;
    const Table& table_;
};

} // namespace SevenPoker