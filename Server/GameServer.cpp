#include "stdafx.h"

#include "Server/GameServer.h"
#include "Server/GameSession.h"

namespace Server {

using namespace Network;

GameServer::GameServer(
    boost::asio::io_context& io_context,
    boost::asio::ip::tcp::endpoint endpoint
) : Listener(io_context, endpoint) {

}

void GameServer::Accepted(boost::asio::ip::tcp::socket socket) {
    auto session = std::make_shared<GameSession>(std::move(socket));
    session->Start();
    sessions_.push_back(session);
}

} // namespace Network
