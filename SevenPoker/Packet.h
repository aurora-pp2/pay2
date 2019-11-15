#pragma once

#include "Utility/Common.h"

namespace Server {
class GameSession;
} // namespace Server

namespace GamePlay {
    class Player;
}

namespace SevenPoker {

class SevenPokerPlayer;

enum PacketType { kReqJoinSevenTable = 20, kResJoinSevenTable, kNotiJoinedPlayer, kNotiOtherPlayerLeaveSevenTable };

struct ReqJoinTable {
    static const size_t kPacketId = kReqJoinSevenTable;
    static bool Handler(std::shared_ptr<Server::GameSession> session, const Payload& payload);

    bool random_table;
    std::string password;
};

struct ResJoinTable {
    static const size_t kPacketId = kResJoinSevenTable;

    ResJoinTable(bool success, int32_t number, const std::string& message);

    bool success_ = false;
    int number_ = 1;
    std::string message_;
    Payload ToJson() const;
};

struct NotiJoinedPlayer {
    static const size_t kPacketId = kNotiJoinedPlayer;

    NotiJoinedPlayer(SevenPokerPlayer* player);
   
    SevenPokerPlayer* player_;
    std::optional<Payload> ToJson() const;
};

/*
struct NotiOtherPlayerLeaveTable {
    static const size_t kPacketId = kNotiOtherPlayerLeaveSevenTable;

    NotiOtherPlayerLeaveTable(bool success, int32_t number, const std::string& message);

    bool success_ = false;
    int number_ = 1;
    std::string message_;
    Payload ToJson();
};
*/

} // namespace SevenPoker