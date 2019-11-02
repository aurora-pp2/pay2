#include "pch.h"
#include "Pay/PaySession.h"
//#include "Utility/json11.hpp"

namespace Network {

static const int kMaxPacketSize = 100;
static std::array<HandlerCallback, kMaxPacketSize> handlers;

static void Fail(Beast::error_code ec, char const* what) {
    if (ec == Net::error::operation_aborted ||
        ec == Beast::websocket::error::closed) {
        return;
    }

    std::cerr << what << ": " << ec.message() << "\n";
}

PaySession::PaySession(tcp::socket socket) : Session(std::move(socket)) {
    for (auto i = 0; i < kMaxPacketSize; ++i) {
        handlers[i] = nullptr;
    }
}

PaySession::~PaySession() {

}

bool PaySession::RegisterHandler(int packet_id, HandlerCallback handler) {
    if (handlers[packet_id] != nullptr) {
        return false;
    }
    handlers[packet_id] = handler;
    return true;
}

void PaySession::OnRead(Beast::error_code ec, std::size_t bytes_transferred) {
    if (!OnHandle(boost::beast::buffers_to_string(buffer_.data()))) {
        Close();
        return;
    }

    if (ec) {
        return Fail(ec, "read");
    }

    Session::OnRead(ec, bytes_transferred);
}

bool PaySession::OnHandle(const std::string& payload) {
    //using namespace json11;
    std::cout << "payload: " << payload << std::endl;
    std::string err;
    const auto json = json11::Json::parse(payload, err);
    if (!err.empty()) {
        return false;
    }

    const int packet_id = json["packet_id"].int_value();
    return handlers[packet_id](std::static_pointer_cast<PaySession>(shared_from_this()), json);
}

} // namespace Network
