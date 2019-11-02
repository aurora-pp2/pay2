#pragma once

#include "Network/Session.h"
#include "Utility/json11.hpp"

namespace Network {

class PaySession;
using Payload = json11::Json;
using HandlerCallback = std::function<bool(std::shared_ptr<PaySession>, const Payload&)>;

class PaySession : public Session {
public:
    explicit PaySession(tcp::socket socket);
    virtual ~PaySession();

    static bool RegisterHandler (int packet_id, HandlerCallback handler);

private:
    void OnRead(Beast::error_code ec, std::size_t bytes_transferred) override;
    bool OnHandle(const std::string& payload) override;

    
};

} // namespace Network
