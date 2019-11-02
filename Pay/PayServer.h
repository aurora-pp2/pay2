#pragma once
#include "Network/Listener.h"

namespace Network {

class Session;

class PayServer : public Listener {
public:
    PayServer(
        boost::asio::io_context& io_context,
        boost::asio::ip::tcp::endpoint endpoint
    );
    virtual ~PayServer() = default;
private:
    void Accepted(tcp::socket socket) override;

    std::vector<SharedPtr<Session>> sessions;
};

} // namespace Network
