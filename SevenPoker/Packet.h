#pragma once

#include "Utility/Common.h"

namespace Server {
class GameSession;
} // namespace Server

namespace SevenPoker {

enum PacketType { kReqJoinSevenPokerTable = 20, kResJoinSevenPokerTable };

struct ReqJoinSevenPokerTable {
    static const size_t kPacketId = PacketType::kReqJoinSevenPokerTable;
    int32_t number = 1;
    std::string message;

    static bool Handler(std::shared_ptr<Server::GameSession> session, const Payload& payload);
};

struct ResJoinSevenPokerTable {
    static const size_t kPacketId = PacketType::kResJoinSevenPokerTable;

    ResJoinSevenPokerTable(bool success, int32_t number, const std::string& message);

    bool success_ = false;
    int number_ = 1;
    std::string message_;
    Payload ToJson();
};

} // namespace SevenPoker