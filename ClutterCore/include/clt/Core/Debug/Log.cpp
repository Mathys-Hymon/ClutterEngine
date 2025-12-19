#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks-inl.h"

namespace clt
{
    std::shared_ptr<spdlog::logger> Core::Log::sCoreLogger;
    std::shared_ptr<spdlog::logger> Core::Log::sClientLogger;

    void Core::Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        sCoreLogger = spdlog::stdout_color_mt("CLUTTER");
        sCoreLogger->set_level(spdlog::level::trace);

        sClientLogger = spdlog::stdout_color_mt("APP");
        sClientLogger->set_level(spdlog::level::trace);
    }
}
