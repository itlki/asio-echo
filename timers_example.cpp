#include <print>
#include <system_error>
#include <vector>

#include <asio.hpp>

int main()
{
    asio::io_context io;

    std::vector<asio::steady_timer> timers;

    for (size_t i = 0; i < 5; ++i) {
        asio::steady_timer t(io, asio::chrono::seconds(i));
        std::println("Waiting for {} seconds", i);
        t.async_wait([i](const std::error_code &e) {
            std::println("Done waiting {} seconds! Error code: {}", i, e.message());
        });
        timers.push_back(std::move(t));
    }

    io.run();
    return 0;
}
