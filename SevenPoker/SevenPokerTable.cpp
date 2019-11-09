#include "stdafx.h"
#include "SevenPoker/SevenPokerTable.h"
#include "SevenPoker/SevenPokerPlayer.h"
#include "Server/GameSession.h"

using namespace GamePlay;

namespace SevenPoker {

std::shared_ptr<SevenPokerPlayer> SevenPokerTable::JoinPlayer(std::shared_ptr<Server::GameSession> session) {
    std::lock_guard<std::mutex> lock_(mutex_);

    if (!is_available_seat()) {
        return nullptr;
    }

    auto player = std::make_shared<SevenPokerPlayer>(*this, session);
    return player;
}

/*
std::vector<std::shared_ptr<GamePlay::Player>> SevenPokerTable::players() const {
    return { seats_.begin(), seats_.end() };
}
*/

bool SevenPokerTable::is_available_seat() const {
    for (const auto& seat : seats_) {
        if (seat == nullptr) {
            return true;
        }
    }
    return false;
}

}