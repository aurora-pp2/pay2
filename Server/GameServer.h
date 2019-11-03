#pragma once

#include "Utility/Common.h"
#include "Network/Listener.h"

namespace Network {
    class Session;
} // namespace Network

namespace Server {

class GameServer : public Network::Listener {
public:
    GameServer(
        boost::asio::io_context& io_context,
        boost::asio::ip::tcp::endpoint endpoint
    );
    virtual ~GameServer() = default;
private:
    void Accepted(boost::asio::ip::tcp::socket socket) override;

    std::vector<SharedPtr<Network::Session>> sessions_;
};

} // namespace Server
