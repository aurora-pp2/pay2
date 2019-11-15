#include "stdafx.h"
#include "Lobby/Packet.h"
#include "Server/GameSession.h"

using Json = json11::Json;

using namespace GamePlay;

namespace Lobby {

// ReqJoinSevenPokerTable
bool ReqUserInfo::Handler(std::shared_ptr<Server::GameSession> session, const Payload& payload) {
    const int number = payload["number"].int_value();
    const std::string& message = payload["message"].string_value();

    std::cout << "message: " << message << std::endl;

    auto user_info = std::make_shared<Server::UserInfo>();

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distribute(1, 1000);
    const auto random_id = distribute(gen);

    user_info->set_id(random_id);
    user_info->set_avatar_path_("asdadasd");
    user_info->set_name("guest" + std::to_string(random_id));
    user_info->financial_status().set_money(100);

    session->set_user_info(user_info);


    session->Send(
        ResUserInfo(
            true, std::to_string(user_info->id()), user_info->name(), user_info->avatar_path(), 
            std::to_string(user_info->financial_status().money())
        ).ToJson()
    );
    
     
    return true;
}

// ResJoinSevenPokerTable
ResUserInfo::ResUserInfo(
    bool success, 
    const std::string& id, 
    const std::string& name, 
    const std::string& avatar_path, 
    const std::string& money
) : success_(success), id_(id), name_(name), avatar_path_(avatar_path), money_(money) {
}

Payload ResUserInfo::ToJson() const {
    Json payload = Json::object{
        { "packet_id", static_cast<int>(kPacketId) },
        { "success", success_ },
        { "id", id_ },
        { "name", name_ },
        { "avatar_path", avatar_path_ },
        { "money", money_ },
    };
    return payload;
}

} // namespace Lobby