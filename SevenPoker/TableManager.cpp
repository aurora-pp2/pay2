#include "stdafx.h"
#include "SevenPoker/TableManager.h"

namespace SevenPoker {

TableManager& TableManager::GetInstance() {
    static TableManager instance;
    return instance;
}


} // namespace SevenPoker