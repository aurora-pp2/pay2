#pragma once

namespace SevenPoker {

class TableManager {
public:
    static TableManager& GetInstance();
    bool Initialize();
};

} // namespace SevenPoker