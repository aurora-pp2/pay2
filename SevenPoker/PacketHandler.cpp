#include "stdafx.h"

#include "SevenPoker/PacketHandler.h"
#include "SevenPoker/Packet.h"

#include "Server/GameSession.h"

namespace SevenPoker {

bool PacketHandler::RegisterHandler() {
    using namespace Server;
    return GameSession::RegisterHandler(ReqJoinTable::kPacketId, ReqJoinTable::Handler);
}

} // namespace SevenPoker