#include "stdafx.h"

#include "SevenPoker/Packet.h"
#include "Server/GameSession.h"

using Json = json11::Json;

namespace SevenPoker {

/****************************************************************************
*
* ReqJoinSevenPokerTable
*
**/
    bool ReqJoinSevenPokerTable::Handler(std::shared_ptr<Server::GameSession> session, const Payload& payload) {
    const int number = payload["number"].int_value();
    const std::string& message = payload["message"].string_value();
    
    std::cout << "message: " << message << std::endl;

    session->Send(ResJoinSevenPokerTable(true, 69, message).ToJson());

    return true;
}

/****************************************************************************
*
* ResJoinSevenPokerTable
*
**/
ResJoinSevenPokerTable::ResJoinSevenPokerTable(
    bool success, 
    int32_t number, 
    const std::string& message
) : success_(success), number_(number), message_(message) {
}

Payload ResJoinSevenPokerTable::ToJson() {
    Json payload = Json::object{
        { "packet_id", static_cast<int>(kPacketId) },
        { "success", success_ },
        { "number", number_ },
        { "message", message_ },
    };
    return payload;
}


} // namespace SevenPoker
