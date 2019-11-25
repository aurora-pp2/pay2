#pragma once

#include "GamePlay/Player.h"

namespace Server {
class UserInfo;
}

namespace SevenPoker {

class Table;

class SevenPokerPlayer : public GamePlay::Player {
public:
    SevenPokerPlayer(std::shared_ptr<Server::GameSession> session, Table* table);
    virtual~SevenPokerPlayer();

    void OnEvent(const GamePlay::Message& msg) override;
    void OnDisconnected() override;

    std::shared_ptr<Server::GameSession> session() const override;

    int32_t table_index() const;
    void set_table_index(int32_t index);

    std::shared_ptr<Server::UserInfo> user_info() const;

private:
    Table* table_ = nullptr;
    std::shared_ptr<Server::UserInfo> user_info_;
    int32_t table_index_ = 0;


    std::mutex mutex_;
};

} // namespace SevenPoker100