#pragma once

#include <functional>
#include <typeindex>

namespace GamePlay {

class Message {
public:
    explicit Message(uint32_t id) : id_(id) {
    }
    virtual ~Message() = default;

    uint32_t id() const {
        return id_;
    }

    template <typename T>
    const T& Cast(const Message& msg) const {
        return static_cast<const T&>(msg);
    }

protected:
    const uint32_t id_;
};

template <typename T>
static auto ToIndex = [](T id) {
    return static_cast<std::underlying_type_t<T>>(id);
};


/*
template <typename T>
const T& Cast(const Message& msg) {
    return static_cast<const T&>(msg);
}
*/

/*
template <typename _Ty>
void Dispatch(MsgHandlerMap& handler_map, const _Ty& msg) {

    auto index = std::type_index(typeid(_Ty));
    const auto it = handler_map.find(index);
    if (it != handler_map.end()) {
        it->second(msg);
    }
}
*/

}