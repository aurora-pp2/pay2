#include "stdafx.h"
#include "Network/Listener.h"
#include "Network/Session.h"

namespace Network {

Listener::Listener(
    Net::io_context& ioc,
    tcp::endpoint endpoint
) : io_context_(ioc), acceptor_(ioc) {
    Beast::error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if (ec) {
        Fail(ec, "open");
        return;
    }

    // Allow address reuse
    acceptor_.set_option(Net::socket_base::reuse_address(true), ec);
    if (ec) {
        Fail(ec, "set_option");
        return;
    }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if (ec) {
        Fail(ec, "bind");
        return;
    }

    // Start listening for connections
    acceptor_.listen(
        Net::socket_base::max_listen_connections, ec);
    if (ec) {
        Fail(ec, "listen");
        return;
    }
}

void Listener::Fail(Beast::error_code ec, char const* what) {
    // Don't report on canceled operations
    if (ec == Net::error::operation_aborted)
        return;
    std::cerr << what << ": " << ec.message() << "\n";
}


void Listener::Run() {
    acceptor_.async_accept(
        Net::make_strand(io_context_),
        Beast::bind_front_handler(
            &Listener::OnAccept,
            shared_from_this()
        )
    );
}

void Listener::OnAccept(Beast::error_code ec, tcp::socket socket) {
    
    if (ec) {
        return Fail(ec, "accept");
    }
    
    Accepted(std::move(socket));
    /*
    std::make_shared<Session>(
        std::move(socket))->Start();
        */

    // The new connection gets its own strand
    acceptor_.async_accept(
        Net::make_strand(io_context_),
        Beast::bind_front_handler(
            &Listener::OnAccept,
            shared_from_this()
        )
    );
}

} // namespace Network
