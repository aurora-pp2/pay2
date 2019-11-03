// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H


#include <csignal>
#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>

#include <boost/asio/io_context.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/smart_ptr.hpp>

template <typename T>
using SharedPtr = std::shared_ptr<T>;

#endif //PCH_H
