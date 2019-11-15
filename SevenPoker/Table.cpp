#include "stdafx.h"
#include "SevenPoker/Table.h"
#include "SevenPoker/SevenPokerPlayer.h"
#include "SevenPoker/Packet.h"

#include "Server/GameSession.h"

using namespace GamePlay;

namespace SevenPoker {

bool Table::is_available_seat() {
    std::lock_guard<std::mutex> lock(mutex_);

    for (const auto& player : players_) {
        if (player == nullptr) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<SevenPokerPlayer> Table::JoinPlayer(std::shared_ptr <Server::GameSession> session) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto player = std::make_shared<SevenPokerPlayer>(session, this);
    auto index = 0;
    for (auto i = 0; i < players_.size(); ++i) {
        if (players_[i] != nullptr) {
            continue;
        }
        players_[i] = player;
        index = i;
    }

    auto payload = NotiJoinedPlayer(player.get()).ToJson();
    if (!payload.has_value()) {
        players_[index] = nullptr;
        return nullptr;
    }

    player->set_table_index(index);

    for (const auto poker_player : players_) {
        const auto player_session = poker_player->session();
        if (player_session != nullptr) {
            player_session->Send(payload.value());
        }
    }

    return player;
}

} // namespace SevenPoker