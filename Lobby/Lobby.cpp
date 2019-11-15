#include "stdafx.h"
#include "Lobby/Lobby.h"
#include "Lobby/PacketHandler.h"

namespace Lobby {

bool Initialize() {
    if (!PacketHandler::RegisterHandler()) {
        std::cout << "[Error] Fail to register handlers" << std::endl;
        return false;
    }
 
    
    return true;
}

} // name Lobby