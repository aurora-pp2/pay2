#include "pch.h"
#include "Pay/PayServer.h"
#include "Pay/PaySession.h"

namespace Network {

PayServer::PayServer(
    boost::asio::io_context& io_context,
    boost::asio::ip::tcp::endpoint endpoint
) : Listener(io_context, endpoint) {

}

void PayServer::Accepted(tcp::socket socket) {
    const auto session = std::make_shared<PaySession>(std::move(socket)); 
    session->Start();
    sessions.push_back(session);
}

} // namespace Network
