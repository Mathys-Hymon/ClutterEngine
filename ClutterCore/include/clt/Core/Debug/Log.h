#pragma once
#include <memory>

#pragma warning(push, 0)

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace clt
{
    namespace Core
    {
        class Log
        {
            static std::shared_ptr<spdlog::logger> sCoreLogger;
            static std::shared_ptr<spdlog::logger> sClientLogger;

        public:
            static void Init();

            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return sClientLogger; }
        };
    }
}

// --- Engine Macro (CORE)

#define CLT_CORE_TRACE(...)          ::clt::Core::Log::GetCoreLogger()->Trace(__VA_ARGS__)
#define CLT_CORE_INFO(...)           ::clt::Core::Log::GetCoreLogger()->Info(__VA_ARGS__)
#define CLT_CORE_WARN(...)           ::clt::Core::Log::GetCoreLogger()->Warn(__VA_ARGS__)
#define CLT_CORE_ERROR(...)          ::clt::Core::Log::GetCoreLogger()->Error(__VA_ARGS__)
#define CLT_CORE_FATAL(...)          ::clt::Core::Log::GetCoreLogger()->Fatal(__VA_ARGS__)

// --- Client Macro (CLIENT)

#define CLUTTER_TRACE(...)         ::clt::Core::Log::GetClientLogger()->Trace(__VA_ARGS__)
#define CLUTTER_INFO(...)          ::clt::Core::Log::GetClientLogger()->Info(__VA_ARGS__)
#define CLUTTER_WARN(...)          ::clt::Core::Log::GetClientLogger()->Warn(__VA_ARGS__)
#define CLUTTER_ERROR(...)         ::clt::Core::Log::GetClientLogger()->Error(__VA_ARGS__)
#define CLUTTER_FATAL(...)         ::clt::Core::Log::GetClientLogger()->Fatal(__VA_ARGS__)