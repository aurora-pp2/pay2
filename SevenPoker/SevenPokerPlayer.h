#pragma once

#include "GamePlay/Player.h"

namespace SevenPoker {

class Table;

class SevenPokerPlayer : public GamePlay::Player {
public:
    SevenPokerPlayer(std::shared_ptr<Server::GameSession> session, Table* table);
    virtual~SevenPokerPlayer();

    void OnEvent(const GamePlay::Message& msg) override;

private:
    std::mutex mutex_;
    Table* table_ = nullptr;
};

} // namespace SevenPoker100