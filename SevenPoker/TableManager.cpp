#include "stdafx.h"
#include "SevenPoker/TableManager.h"
#include "SevenPoker/Table.h"
#include "Server/GameSession.h"

namespace SevenPoker {

TableManager& TableManager::GetInstance() {
    static TableManager instance;
    return instance;
}

bool TableManager::Initialize() {
    return true;
}

std::shared_ptr<SevenPokerPlayer> TableManager::JoinTable(std::shared_ptr<Server::GameSession> session) {
    std::lock_guard<std::mutex> lock_(mutex_);

    for (const auto&[key, table] : tables_) {
        if (table->is_available_seat()) {
            return table->JoinPlayer(session);
        }
    }

    auto table = std::make_unique<Table>();
    const auto&[it, result] = tables_.try_emplace(table.get(), std::move(table));
    if (!result) {
        return nullptr;
    }
    return it->second->JoinPlayer(session);
}
/*
std::shared_ptr<SevenPokerPlayer> TableManager::TryJoinTable(
    std::shared_ptr<Server::GameSession> session
) {
    std::lock_guard<std::mutex> lock_(mutex_);

    for (const auto& [ptr, table] : tables_) {
        auto player = table->JoinPlayer(session);
        if(player != nullptr) {
            return player;
        }
    }

    auto table = std::make_shared<Table>();
    const auto& [it, result] = tables_.try_emplace(table.get(), table);
    if (!result) {
        return nullptr;
    }
    return it->second->JoinPlayer(session);
}
*/

} // namespace SevenPoker
