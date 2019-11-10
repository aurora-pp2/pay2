#pragma once

namespace Server {
    class GameSession;
}

namespace GamePlay {
    class Player;
}

namespace SevenPoker {

class Table;
class SevenPokerPlayer;
    
class TableManager {
public:
    static TableManager& GetInstance();
    bool Initialize();

    //std::shared_ptr<SevenPokerPlayer> TryJoinTable(std::shared_ptr<Server::GameSession> session);

private:
    std::map<const Table*, std::shared_ptr<Table>> tables_;
    std::mutex mutex_;
};

} // namespace SevenPoker