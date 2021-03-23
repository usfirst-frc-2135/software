#include <chrono>
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace frc2135
{
    void initialize_spdlog()
    {
        spdlog::init_thread_pool(256, 1);
        spdlog::flush_every(std::chrono::seconds(1));

        auto rotating_logger =
            std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/rotating.txt", 10 * 1024 * 1024, 5);
        auto stdout_logger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        auto logger = std::make_shared<spdlog::async_logger>(
            "spdlog",
            spdlog::sinks_init_list{
                rotating_logger,
                stdout_logger,
            },
            spdlog::thread_pool(),
            spdlog::async_overflow_policy::overrun_oldest);

        spdlog::set_default_logger(logger); // keeps the logger alive
        spdlog::info("spdlog default logger set");
    }
} // namespace frc2135
