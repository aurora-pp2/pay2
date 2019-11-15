#include "stdafx.h"
#include "Server/GameSession.h"

#include "GamePlay/Player.h"

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

/****************************************************************************
*
* FinancialStatus
*
**/
int64_t FinancialStatus::money() const {
    return money_;
}

void FinancialStatus::set_money(int64_t money) {
    money_ = money;
}

void FinancialStatus::SetDeltaMoney(int64_t delta_money) {
    money_ = std::max<int64_t>(0, money_ + delta_money);
}

/****************************************************************************
*
* UserInfo
*
**/
size_t UserInfo::id() const {
    return id_;
}

void UserInfo::set_id(size_t id) {
    id_ = id;
}

const std::string& UserInfo::name() const {
    return name_;
}

void UserInfo::set_name(const std::string& name) {
    name_ = name;
}

const std::string& UserInfo::avatar_path() const {
    return avatar_path_;
}

void UserInfo::set_avatar_path_(const std::string& avatar_path) {
    avatar_path_ = avatar_path;
}

FinancialStatus& UserInfo::financial_status() {
    return financial_status_;
}

/****************************************************************************
*
* GameSession
*
**/
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
    const std::string json_str = payload.dump();
    Session::Send(std::make_shared<std::string>(std::move(json_str)));
}

void GameSession::OnRead(boost::beast::error_code ec, std::size_t bytes_transferred) {
    if (ec) {
        Fail(ec, "[Error] OnRead error_code");
        return OnDisconnected(ec);
    }

    if (bytes_transferred <= 0) {
        Fail(ec, "[Error] OnRead bytes_transferred");
        return OnDisconnected(ec);
    }

    if (!OnHandle(boost::beast::buffers_to_string(buffer_.data()))) {
        Close();
        return;
    }

    Session::OnRead(ec, bytes_transferred);
}

void GameSession::OnDisconnected(boost::beast::error_code ec) {
    auto player = player_.lock();
    if (player != nullptr) {
        player->OnDisconnected();
    }
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

std::shared_ptr<UserInfo>GameSession::user_info() const {
    std::shared_ptr<UserInfo>user_info = std::atomic_load(&user_info_);
    return user_info;
}

void GameSession::set_user_info(std::shared_ptr<UserInfo> user_info) {
    std::atomic_exchange(&user_info_, user_info);
}

} // namespace Network
