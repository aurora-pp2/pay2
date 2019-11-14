#pragma once

#include "GamePlay/Message.h"

namespace SevenPoker {

enum MessageType : uint32_t {
    kIntMessage = 20,
    kFloatMessage,
};

class IntMessage : public GamePlay::Message {
public:
    IntMessage() : Message(kIntMessage) {
        
    }
    virtual ~IntMessage() = default;
    
    int a = 18;
};

class FloatMessage : public GamePlay::Message {
public:
    FloatMessage() : Message(kFloatMessage) {

    }
    virtual ~FloatMessage() = default;
    float a = 21.5;
};

}

