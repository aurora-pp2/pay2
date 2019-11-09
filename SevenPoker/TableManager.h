#pragma once

namespace Server {
    class GameSession;
}

namespace GamePlay {
    class Player;
}

namespace SevenPoker {

class Table;
    
class TableManager {
public:
    static TableManager& GetInstance();
    bool Initialize();

    std::shared_ptr<GamePlay::Player> TryJoinTable(std::shared_ptr<Server::GameSession> session);

private:
    std::map<const Table*, std::shared_ptr<Table>> tables_;
    std::mutex mutex_;
};

} // namespace SevenPoker