#include "stdafx.h"
#include "SevenPoker/SevenPokerPlayer.h"
#include "SevenPoker/Table.h"
#include "SevenPoker/Message.h"

using namespace GamePlay;

namespace SevenPoker {

using MessageHandler = std::function<void(SevenPokerPlayer& player, const Message& msg)>;

static void HandleIntMessage(SevenPokerPlayer& player, const Message& msg) {
    auto m = msg.Cast<IntMessage>(msg);
    std::cout << "suck:" << m.a << std::endl;

}

static void HandleFloatMessage(SevenPokerPlayer& player, const Message& msg) {
    auto m = msg.Cast<FloatMessage>(msg);
    std::cout << "suck:" << m.a << std::endl;

}

static std::unordered_map<uint32_t, MessageHandler> handlers = {
    std::make_pair(kIntMessage, HandleIntMessage),
    std::make_pair(kFloatMessage, HandleFloatMessage)
};

SevenPokerPlayer::SevenPokerPlayer(
    Table& table,
    std::shared_ptr<Server::GameSession> session
) : Player(session), table_(table) {

    //handlers[kIntMessage] = HandleIntMessage;
}

SevenPokerPlayer::~SevenPokerPlayer() = default;

void SevenPokerPlayer::OnEvent(const Message& msg) {
    auto it = handlers.find(msg.id());
    if (it != handlers.end()) {
        it->second(*this, msg);
    }
   
}

} // namespace SevenPoker