#include "pch.h"

#include "Pay/PayServer.h"
//#include <windows.h>

//#pragma comment(lib,"Advapi32")

static std::mutex m;
static std::condition_variable cv;
static std::atomic_bool is_stop = false;
static const int thread_count = 1;

static void SignalHandler(int /*signal_val*/) {
    //std::sig_atomic_t v = signal_val;
    is_stop = true;
    cv.notify_all();
}

int main() {
    // 서버 종료 ctrl + break
    std::signal(SIGBREAK, SignalHandler);

    // 로케일 설정
    setlocale(LC_ALL, "");
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    std::unique_lock<std::mutex> lock(m);

    // The io_context is required for all I/O
    boost::asio::io_context io_context { thread_count };

    const auto address = boost::asio::ip::make_address("127.0.0.1");

    std::make_shared<Network::PayServer>(
        io_context,
        boost::asio::ip::tcp::endpoint{ address, 3000 }
    )->Run();

    wprintf(L"서버 부트업\n");

    std::vector<std::thread> v;
    v.reserve(thread_count - 1);
    for (auto i = thread_count - 1; i > 0; --i)
        v.emplace_back(
            [&io_context]
    {
        io_context.run();
    });
    io_context.run();

    cv.wait(lock, [] {
        if (is_stop) {
            wprintf(L"서버 종료 알림\n");
            return true;
        }
        wprintf(L"메인 스레드 대기\n");
        return false;
    });

    wprintf(L"서버 종료 Press any key to close this window.\n"); 
    getchar();
    return 0;
}
