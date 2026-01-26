#include <clt/Core/Debug/Log.h>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace clt
{
    namespace Core
    {
        std::shared_ptr<spdlog::logger> Log::sCoreLogger;
        std::shared_ptr<spdlog::logger> Log::sClientLogger;

        void Log::Init()
        {
            spdlog::set_pattern("%^[%T] [%l] %s:%# > %v%$");

            sCoreLogger = spdlog::stdout_color_mt("CLUTTER");
            sCoreLogger->set_level(spdlog::level::trace);

            sClientLogger = spdlog::stdout_color_mt("APP");
            sClientLogger->set_level(spdlog::level::trace);
        }
    }
}
