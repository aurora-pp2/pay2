// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// reference additional headers your program requires here
#include <memory>
#include <array>
#include <iostream>
#include <mutex>
#include <map>

#include <boost/asio/io_context.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/smart_ptr.hpp>