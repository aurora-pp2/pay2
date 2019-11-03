#include "stdafx.h"

#include "SevenPoker/PacketHandler.h"
#include "SevenPoker/Packet.h"

#include "Server/GameSession.h"

namespace SevenPoker {

bool PacketHandler::RegisterHandler() {
    using namespace Server;

    if (!GameSession::RegisterHandler(ReqJoinSevenPokerTable::kPacketId, ReqJoinSevenPokerTable::Handler)) return false;

    return true;
}

} // namespace SevenPoker