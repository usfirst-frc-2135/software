#include <chrono>
#include <frc/Filesystem.h>
#include <spdlog/async.h>
#include <spdlog/fmt/chrono.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string>
#include <wpi/SmallString.h>

namespace frc2135
{
    void handle_spdlog_error(const std::string &msg)
    {
        // Log when an error occurs within spdlog
        spdlog::error("*** SPDLOG ERROR ***: {}", msg);
    }

    void initialize_spdlog()
    {
        wpi::SmallString<64> operating_directory;
        frc::filesystem::GetOperatingDirectory(operating_directory);

        try
        {
            spdlog::init_thread_pool(256, 1);
            spdlog::flush_every(std::chrono::seconds(1));

            auto basic_file_logger = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format(
                "{}/logs/{:%Y-%m-%d_%H-%M-%S}.log",
                operating_directory.c_str(),
                std::chrono::system_clock::now()));
            auto stdout_logger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

            auto logger = std::make_shared<spdlog::async_logger>(
                "2135",
                spdlog::sinks_init_list{
                    basic_file_logger,
                    stdout_logger,
                },
                spdlog::thread_pool(),
                spdlog::async_overflow_policy::overrun_oldest);

            spdlog::set_default_logger(logger); // keeps the logger alive
            spdlog::set_error_handler(handle_spdlog_error);

            spdlog::info("spdlog initialized");
        }
        catch (spdlog::spdlog_ex e)
        {
            // If initialization fails,  print the exception and fall back to the default stdout logger
            spdlog::error("*** SPDLOG EXCEPTION DURING INITIALIZATION: {} ***", e.what());
        }
    }
} // namespace frc2135
