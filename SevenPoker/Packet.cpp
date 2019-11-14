#include "stdafx.h"
#include "SevenPoker/Packet.h"

// outer project
#include "Server/GameSession.h"
//#include "GamePlay/Player.h"

// inner project 
#include "SevenPoker/TableManager.h"
#include "SevenPoker/Table.h"
#include "SevenPoker/SevenPokerPlayer.h"
#include "Message.h"

using Json = json11::Json;

using namespace GamePlay;

namespace SevenPoker {

/****************************************************************************
*
* ReqJoinSevenPokerTable
*
**/
bool ReqJoinTable::Handler(std::shared_ptr<Server::GameSession> session, const Payload& payload) {
    const int number = payload["number"].int_value();
    const std::string& message = payload["message"].string_value();
    
    std::cout << "message: " << message << std::endl;

    const Table* table = TableManager::GetInstance().GetTable();
    if (table == nullptr) {
        return false;
    }



    /*
    Table t;
    auto p = std::make_shared<SevenPokerPlayer>(t, session);
    session->set_player(p);
    
    auto player = session->player();
    FloatMessage msg;
    player->OnEvent(msg);
    */
    /*
    if (player != nullptr) {
        auto seven_poker_player = static_cast<SevenPokerPlayer*>(player.get());
        seven_poker_player->UniqueFunction();
    }
    */
    /*
    std::shared_ptr<Player> player = TableManager::GetInstance().TryJoinTable(session);
    if (player == nullptr) {
        session->Send(ResJoinTable(true, 69, message).ToJson());
        return true;
    }

    session->set_player(player);
    */
    
    //session->Send(ResJoinSevenPokerTable(true, 69, message).ToJson());

    return true;
}

/****************************************************************************
*
* ResJoinSevenPokerTable
*
**/
ResJoinTable::ResJoinTable(
    bool success, 
    int32_t number, 
    const std::string& message
) : success_(success), number_(number), message_(message) {
}

Payload ResJoinTable::ToJson() const {
    Json payload = Json::object{
        { "packet_id", static_cast<int>(kPacketId) },
        { "success", success_ },
        { "number", number_ },
        { "message", message_ },
    };
    return payload;
}

/****************************************************************************
*
* ResJoinSevenPokerTable
*
**/
NotiTablePlayerInfo::NotiTablePlayerInfo(GamePlay::Player* player) : player_(player) {

}

Payload NotiTablePlayerInfo::ToJson() const {
    std::vector<Json> payload;
    /*
    const Table& table = player_->table();
    for (const auto player : table.players()) {
        bool is_valid = false;
        if (player != nullptr) {
            is_valid = true;
        }

        Json json = Json::object{
                    { "packet_id", static_cast<int>(kPacketId) },
                    { "valid", is_valid },
        };
        payload.push_back(json);
    }
    */

    return payload;
}

} // namespace SevenPoker
