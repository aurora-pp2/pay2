#pragma once

#include "Utility/Common.h"

namespace Server {
    class GameSession;
} // namespace Server

namespace GamePlay {
    class Player;
}

namespace Lobby {

enum PacketType { kReqUserInfo = 0, kResUserInfo };

struct ReqUserInfo {
    static const size_t kPacketId = kReqUserInfo;
    static bool Handler(std::shared_ptr<Server::GameSession> session, const Payload& payload);

    size_t number;
    std::string message;
};

struct ResUserInfo {
    static const size_t kPacketId = kResUserInfo;

    ResUserInfo(
        bool success, 
        const std::string& id, 
        const std::string& name, 
        const std::string& avatar_path,
        const std::string& money
    );

    bool success_ = false;
    std::string uid_;
    std::string name_;
    std::string avatar_path_;
    std::string money_;

    Payload ToJson() const;
};

} // namespace Lobby