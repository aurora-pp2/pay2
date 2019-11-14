#include "stdafx.h"
#include "SevenPoker/SevenPokerPlayer.h"
#include "SevenPoker/Table.h"
#include "SevenPoker/Message.h"

using namespace GamePlay;

namespace SevenPoker {

using MessageHandler = std::function<void(SevenPokerPlayer& player, const Message& msg)>;

static void HandleIntMessage(SevenPokerPlayer& player, const Message& msg) {
    auto int_message = msg.Cast<IntMessage>(msg);
    std::cout << "suck:" << int_message.a << std::endl;

}

static void HandleFloatMessage(SevenPokerPlayer& player, const Message& msg) {
    auto float_message = msg.Cast<FloatMessage>(msg);
    std::cout << "suck:" << float_message.a << std::endl;
}

static const std::unordered_map<uint32_t, MessageHandler> handlers = {
    std::make_pair(kIntMessage, HandleIntMessage),
    std::make_pair(kFloatMessage, HandleFloatMessage)
};

SevenPokerPlayer::SevenPokerPlayer(
    std::shared_ptr<Server::GameSession> session,
    Table* table
) : Player(session), table_(table) {
}


SevenPokerPlayer::~SevenPokerPlayer() = default;

void SevenPokerPlayer::OnEvent(const Message& msg) {
    const auto it = handlers.find(msg.id());
    if (it != handlers.end()) {
        it->second(*this, msg);
    }
}

std::shared_ptr<Server::GameSession> SevenPokerPlayer::session() const {
    return session_.lock();
}

} // namespace SevenPoker