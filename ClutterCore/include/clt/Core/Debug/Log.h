#pragma once
#include <memory>

#if defined(_MSC_VER) // PC
    #define CLT_DEBUGBREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__) // 3DS
    #define CLT_DEBUGBREAK() __builtin_trap()
#else
    #define CLT_DEBUGBREAK()

#endif

#include <spdlog/spdlog.h>
#include <spdlog/common.h>

namespace clt::core
{
    class Log
    {
        static std::shared_ptr<spdlog::logger> sCoreLogger;
        static std::shared_ptr<spdlog::logger> sClientLogger;

    public:
        static void Init();
        static void AddSink(spdlog::sink_ptr sink);

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return sClientLogger; }
    };
}

namespace clt::log
{
    // --- Engine Macros (CORE) ---

#ifdef CLT_DEBUG // DEBUG MODE
#define CLT_CORE_TRACE(...)    ::clt::core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
#define CLT_CORE_INFO(...)     ::clt::core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define CLT_CORE_WARN(...)     ::clt::core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define CLT_CORE_ERROR(...)    ::clt::core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
#define CLT_CORE_FATAL(...)    ::clt::core::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)
#define CLT_CORE_ASSERT(x, ...) { if(!(x)) { CLT_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); CLT_DEBUGBREAK(); } }

#else // RELEASE MODE#define CLT_CORE_TRACE(...)
#define CLT_CORE_INFO(...)
#define CLT_CORE_WARN(...)
#define CLT_CORE_ERROR(...)
#define CLT_CORE_FATAL(...)
#define CLT_CORE_ASSERT(x, ...)
#endif

// --- Client Macros (CLIENT) ---

#ifdef CLT_DEBUG // DEBUG MODE
#define CLUTTER_TRACE(...)     ::clt::core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
#define CLUTTER_INFO(...)      ::clt::core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define CLUTTER_WARN(...)      ::clt::core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define CLUTTER_ERROR(...)     ::clt::core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
#define CLUTTER_FATAL(...)     ::clt::core::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)
#define CLUTTER_ASSERT(x, ...) { if(!(x)) { CLUTTER_ERROR("[client] Assertion Failed: {}", __VA_ARGS__); CLT_DEBUGBREAK(); } }
#else
#define CLUTTER_TRACE(...)
#define CLUTTER_INFO(...)
#define CLUTTER_WARN(...)
#define CLUTTER_ERROR(...)
#define CLUTTER_FATAL(...)
#define CLUTTER_ASSERT(x, ...)
#endif
}
