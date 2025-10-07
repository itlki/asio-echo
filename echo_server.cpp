#include <print>
#include <memory>
#include <asio.hpp>

using asio::ip::tcp;
using std::println;

const size_t port = 6969;
asio::io_context io;
asio::ip::tcp::acceptor server(io, tcp::endpoint(tcp::v4(), port));

class Request {
public:
    explicit Request(tcp::socket &&socket):
        socket(std::move(socket))
    {}

    tcp::socket socket;
    asio::streambuf buffer;
};

void handle_request(const std::error_code& ec, tcp::socket socket) {
    server.async_accept(io, &handle_request); // The Loop

    auto request = std::make_shared<Request>(std::move(socket));

    auto ep = request->socket.remote_endpoint();
    println("Accepted connection {}", ep.address().to_string());

    asio::async_read_until(request->socket, request->buffer, '\n',
        [request](const auto &error, size_t bytes_transferred) {
            auto ep = request->socket.remote_endpoint();
            println("Received {} bytes from {}", bytes_transferred, ep.address().to_string());
            asio::async_write(request->socket, request->buffer,
                [request](const auto &error, size_t bytes_transferred) {
                    auto ep = request->socket.remote_endpoint();
                    println("Sent {} bytes to {}", bytes_transferred, ep.address().to_string());
                });
        });
}

int main()
{
    size_t seconds = 5;
    asio::steady_timer t(io, asio::chrono::seconds(seconds));
    println("Waiting for {} seconds", seconds);
    t.async_wait([seconds](const std::error_code &e) {
        println("------------------------------");
        println("Done waiting {} seconds. Error: {}", seconds, e.message());
        println("------------------------------");
    });

    println("Listening too 127.0.0.1:{}", port);
    server.async_accept(io, &handle_request);
    io.run();

    return 0;
}
