// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

/*
template <typename T>
using MakeShared = boost::make_shared<T>;
*/

// reference additional headers your program requires here

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <memory>
#include <string_view>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/smart_ptr.hpp>

namespace Beast = boost::beast;         // from <boost/beast.hpp>
namespace Http = Beast::http;           // from <boost/beast/http.hpp>
namespace WebSocket = Beast::websocket; // from <boost/beast/websocket.hpp>
namespace Net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

template <typename T>
using SharedPtr = std::shared_ptr<T>;
