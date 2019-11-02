#pragma once

enum PacketType { ReqJoinSevenPokerTable = 200, ResJoinSevenPokerTable };

struct ReqJoinSevenPokerTable {
    static const size_t packet_id = PacketType::ReqJoinSevenPokerTable;
    int32_t number = 1;
};

struct ResJoinSevenPokerTable {
    static const size_t packet_id = PacketType::ResJoinSevenPokerTable;
    bool success = false;
    int32_t number = 1;
};
