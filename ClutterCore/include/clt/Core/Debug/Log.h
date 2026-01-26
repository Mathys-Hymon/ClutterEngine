#pragma once
#include <memory>

#pragma warning(push, 0)

#include <spdlog/spdlog.h>
#include <spdlog/common.h>

#pragma warning(pop)

namespace clt::Core
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

// --- Engine Macros (CORE) ---

#define CLT_CORE_TRACE(...)    ::clt::Core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
#define CLT_CORE_INFO(...)     ::clt::Core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define CLT_CORE_WARN(...)     ::clt::Core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define CLT_CORE_ERROR(...)    ::clt::Core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
#define CLT_CORE_FATAL(...)    ::clt::Core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)

// --- Client Macros (CLIENT) ---

#define CLUTTER_TRACE(...)     ::clt::Core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
#define CLUTTER_INFO(...)      ::clt::Core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define CLUTTER_WARN(...)      ::clt::Core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define CLUTTER_ERROR(...)     ::clt::Core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
#define CLUTTER_FATAL(...)     ::clt::Core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)