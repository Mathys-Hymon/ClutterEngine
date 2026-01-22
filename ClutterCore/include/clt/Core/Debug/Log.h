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

#define CLT_CORE_TRACE(...)          ::clt::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CLT_CORE_INFO(...)           ::clt::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CLT_CORE_WARN(...)           ::clt::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CLT_CORE_ERROR(...)          ::clt::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CLT_CORE_FATAL(...)          ::clt::Core::Log::GetCoreLogger()->critical(__VA_ARGS__)

// --- Client Macro (CLIENT)

#define CLUTTER_TRACE(...)         ::clt::Core::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLUTTER_INFO(...)          ::clt::Core::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLUTTER_WARN(...)          ::clt::Core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLUTTER_ERROR(...)         ::clt::Core::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLUTTER_FATAL(...)         ::clt::Core::Log::GetClientLogger()->critical(__VA_ARGS__)