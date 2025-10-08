#include <cstdio>
#include <system_error>
#include <vector>

#include <asio.hpp>

int main()
{
    asio::io_context io;

    std::vector<asio::steady_timer> timers;

    for (size_t i = 0; i < 5; ++i) {
        asio::steady_timer t(io, asio::chrono::seconds(i));
        printf("Waiting for %zu seconds\n", i);
        t.async_wait([i](const std::error_code &e) {
            printf("Done waiting %zu seconds! Error: %s", i, e.message().c_str());
        });
        timers.push_back(std::move(t));
    }

    io.run();
    return 0;
}
