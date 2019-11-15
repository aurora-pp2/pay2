#pragma once

#include "Network/Session.h"
#include "Utility/Common.h"
#include <memory>

namespace GamePlay {
class Player;
} // namespace GamePlay

namespace Server {

class GameSession;

using HandlerCallback = std::function<bool(std::shared_ptr<GameSession>, const Payload&)>;

class FinancialStatus {
public:
    int64_t money() const;
    void set_money(int64_t money);
    void SetDeltaMoney(int64_t delta_money);

private:
    int64_t money_ = 0;
};

class UserInfo {
public:
    FinancialStatus& financial_status();

    size_t id() const;
    void set_id(size_t id);

    const std::string& name() const;
    void set_name(const std::string& id);

    const std::string& avatar_path() const;
    void set_avatar_path_(const std::string& avatar_path);

private:
    size_t id_;
    std::string name_;
    std::string avatar_path_;
    FinancialStatus financial_status_;
};

class GameSession : public Network::Session {
public:
    explicit GameSession(boost::asio::ip::tcp::socket socket);
    virtual ~GameSession();

    static bool RegisterHandler(int packet_id, HandlerCallback handler);

    void Send(const Payload& payload);

    std::shared_ptr<GamePlay::Player> player() const;
    void set_player(std::shared_ptr<GamePlay::Player> player);

    size_t uid() const;
    void set_uid(size_t uid);

    std::shared_ptr<UserInfo> user_info() const;
    void set_user_info(std::shared_ptr<UserInfo> user_info);

private:
    void OnRead(boost::beast::error_code ec, std::size_t bytes_transferred) override;
    bool OnHandle(const std::string& payload) override;
    void OnDisconnected(boost::beast::error_code ec) override;

    size_t uid_;
    
    std::shared_ptr<UserInfo> user_info_;

    std::weak_ptr<GamePlay::Player> player_;
    std::mutex mutex_;
};

} // namespace Server
