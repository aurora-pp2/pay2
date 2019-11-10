#include "stdafx.h"
#include "SevenPoker/SevenPokerPlayer.h"
#include "SevenPoker/Table.h"

using namespace GamePlay;

namespace SevenPoker {

SevenPokerPlayer::SevenPokerPlayer(
    Table& table,
    std::shared_ptr<Server::GameSession> session
) : Player(session), table_(table) {

}

SevenPokerPlayer::~SevenPokerPlayer() = default;


} // namespace SevenPoker