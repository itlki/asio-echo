#include <print>
#include <asio.hpp>

using asio::ip::tcp;

const size_t port = 6970;
asio::io_context io;

asio::awaitable<void> echo(tcp::socket socket)
{
    char data[1024];
    std::size_t n = co_await socket.async_read_some(asio::buffer(data), asio::use_awaitable);
    std::println("Read {} bytes", n);
    n = co_await async_write(socket, asio::buffer(data, n), asio::use_awaitable);
    std::println("Wrote {} bytes", n);
}

asio::awaitable<void> accept_loop(tcp::acceptor server)
{
    while (true) {
        tcp::socket socket = co_await server.async_accept(io, asio::use_awaitable);
        std::println("Connection accepted");
        asio::co_spawn(io, echo(std::move(socket)), asio::detached);
    }
}

int main()
{
    tcp::acceptor server(io, tcp::endpoint(tcp::v4(), port));
    asio::co_spawn(io, accept_loop(std::move(server)), asio::detached);
    std::println("Listening to 0.0.0.0:{}", port);
    io.run();
    return 0;
}
