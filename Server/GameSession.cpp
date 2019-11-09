#include "stdafx.h"

#include "Server/GameSession.h"

using namespace Network;

namespace Server {

static const int kMaxPacketSize = 300;
static std::array<HandlerCallback, kMaxPacketSize> handlers = { nullptr, };

static void Fail(boost::beast::error_code ec, char const* what) {
    if (ec == boost::asio::error::operation_aborted ||
        ec == boost::beast::websocket::error::closed) {
        return;
    }

    std::cerr << what << ": " << ec.message() << "\n";
}

GameSession::GameSession(boost::asio::ip::tcp::socket socket) : Session(std::move(socket)) {
}

GameSession::~GameSession() {

}

bool GameSession::RegisterHandler(int packet_id, HandlerCallback handler) {
    if (handlers[packet_id] != nullptr) {
        return false;
    }
    handlers[packet_id] = handler;
    return true;
}

void GameSession::Send(const Payload& payload) {
    std::string json_str = payload.dump();
    Session::Send(std::make_shared<std::string>(std::move(json_str)));
}

void GameSession::OnRead(boost::beast::error_code ec, std::size_t bytes_transferred) {
    if (!OnHandle(boost::beast::buffers_to_string(buffer_.data()))) {
        Close();
        return;
    }

    if (ec) {
        return Fail(ec, "read");
    }

    Session::OnRead(ec, bytes_transferred);
}

bool GameSession::OnHandle(const std::string& payload) {

    std::cout << "payload: " << payload << std::endl;
    std::string err;
    const auto json = json11::Json::parse(payload, err);
    if (!err.empty()) {
        return false;
    }

    const int packet_id = json["packet_id"].int_value();

    if (handlers[packet_id] == nullptr) {
        return false;
    }
    return handlers[packet_id](std::static_pointer_cast<GameSession>(shared_from_this()), json);
}

std::shared_ptr<GamePlay::Player> GameSession::player() const {
    //std::shared_ptr<GamePlay::Player>player = std::atomic_load(&player_);
    return player_.lock();
}

void GameSession::set_player(std::shared_ptr<GamePlay::Player> player) {
    //std::atomic_exchange(&player_, player);
    player_ = player;
}

size_t GameSession::uid() const {
    return uid_;
}

void GameSession::set_uid(size_t uid) {
    uid_ = uid;
}

} // namespace Network
