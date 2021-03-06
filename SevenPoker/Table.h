#pragma once

namespace Network {
class Session;
} // namespace Network

namespace Server {
class GameSession;
}

namespace SevenPoker {

class SevenPokerPlayer;

class Table {
public:
    static const size_t kMaxPlayer = 5;

    ~Table() {}
    
    bool is_available_seat();
    std::shared_ptr<SevenPokerPlayer> JoinPlayer(std::shared_ptr <Server::GameSession> session);
    const std::array<std::shared_ptr<SevenPokerPlayer>, kMaxPlayer>& players() const;

private:
    std::mutex mutex_;
    std::array<std::shared_ptr<SevenPokerPlayer>, kMaxPlayer> players_ = { nullptr, };
};

}
