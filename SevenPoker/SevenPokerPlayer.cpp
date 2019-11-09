#include "stdafx.h"
#include "SevenPoker/SevenPokerPlayer.h"

using namespace GamePlay;

namespace SevenPoker {

SevenPokerPlayer::SevenPokerPlayer(
    SevenPokerTable& table,
    std::shared_ptr<Server::GameSession> session
) : Player(session), table_(table) {

}

SevenPokerPlayer::~SevenPokerPlayer() = default;


} // namespace SevenPoker