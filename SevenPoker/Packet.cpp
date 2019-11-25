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
    const bool is_random_table = payload["is_random_table"].bool_value();
    const std::string password = payload["password"].string_value();
    
    const auto player = TableManager::GetInstance().JoinTable(session);
    if (player == nullptr) {
        return false;
    }

    session->set_player(player);

    //player->OnEvent()
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
    const Table* table
) : table_(table) {
}

Payload ResJoinTable::ToJson() const {
    //Json payload;
    const std::array<std::shared_ptr<SevenPokerPlayer>, Table::kMaxPlayer>& players = table_->players();
    std::vector<Json::object> json_objects;
    for (auto index = 0; index < players.size(); ++index) {
        if (players[index] != nullptr) {
            const auto user_info = players[index]->user_info();
            if (user_info == nullptr) {
                continue;
            }
           auto json_object = Json::object{
               { "uid", std::to_string(user_info->uid()) },
               { "name", user_info->name() },
               { "money", std::to_string(user_info->financial_status().money()) },
               { "table_index", index }
            };
            json_objects.push_back(json_object);
        }
    }
    return { json_objects };
}

/****************************************************************************
*
* ResJoinSevenPokerTable
*
**/
NotiJoinedPlayer::NotiJoinedPlayer(SevenPokerPlayer* player) : player_(player) {

}

std::optional<Json> NotiJoinedPlayer::ToJson() const {
    const auto session = player_->session();
    if (session == nullptr) {
        return {};
    }

    auto user_info = session->user_info();
    if (user_info == nullptr) {
        return {};
    }
    Json payload = Json::object { 
        { "id", std::to_string(user_info->uid()) },
        { "name", user_info->name() },
        { "money", std::to_string(user_info->financial_status().money()) },
        { "seat_index", player_->table_index() }
    };
    //std::vector<Json> payload;
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
