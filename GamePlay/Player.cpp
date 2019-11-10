#include "stdafx.h"
#include "Player.h"

namespace GamePlay {

Player::Player(std::shared_ptr<Server::GameSession> session) : session_(session) {
}


Player::~Player() {

}

} // namespace GamePlay
