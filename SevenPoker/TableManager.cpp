#include "stdafx.h"
#include "SevenPoker/TableManager.h"
#include "Server/GameSession.h"

namespace SevenPoker {

TableManager& TableManager::GetInstance() {
    static TableManager instance;
    return instance;
}

bool TableManager::Initialize() {
    return true;
}


} // namespace SevenPoker
