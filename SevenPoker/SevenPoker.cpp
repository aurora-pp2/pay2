#include "stdafx.h"

#include "SevenPoker/SevenPoker.h"
#include "SevenPoker/TableManager.h"
#include "SevenPoker/PacketHandler.h"

namespace SevenPoker {

bool Initialize() {
    if (!PacketHandler::RegisterHandler()) {
        std::cout << "[Error] Fail to register handlers" << std::endl;
        return false;
    }
    if (!TableManager::GetInstance().Initialize()) {
        std::cout << "[Error] Fail to initialize table manager" << std::endl;
        return false;
    }
    return true;
}

} // namespace SevenPoker;
