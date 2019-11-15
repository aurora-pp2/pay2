#include "stdafx.h"

#include "Lobby/PacketHandler.h"
#include "Lobby/Packet.h"

#include "Server/GameSession.h"

namespace Lobby {

bool PacketHandler::RegisterHandler() {
    using namespace Server;
    if (!GameSession::RegisterHandler(ReqUserInfo::kPacketId, ReqUserInfo::Handler)) {
        return false;
    }
    
    return true;
    //return GameSession::RegisterHandler(ReqJoinTable::kPacketId, ReqJoinTable::Handler);
}

} // namespace Lobby