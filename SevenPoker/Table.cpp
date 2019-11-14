#include "stdafx.h"
#include "SevenPoker/Table.h"
#include "SevenPoker/SevenPokerPlayer.h"
#include "Server/GameSession.h"

using namespace GamePlay;

namespace SevenPoker {

bool Table::is_available_seat() {
    std::lock_guard<std::mutex> lock(mutex_);

    for (const auto& seat : seats_) {
        if (seat == nullptr) {
            return true;
        }
    }
    return false;
}

} // namespace SevenPoker