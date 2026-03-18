#ifndef CLUTTERENGINE_LOGHISTORY_H
#define CLUTTERENGINE_LOGHISTORY_H
#include <deque>
#include <string>

#include "spdlog/common.h"

namespace editor::log
{
    struct ConsoleMessage
    {
        std::string message;
        spdlog::level::level_enum level;
    };

    class LogHistory
    {
        static std::deque<ConsoleMessage> mLogs;
        static std::mutex mLogMutex;

    public:
        static void AddLog(ConsoleMessage& message);
        static const std::deque<ConsoleMessage>& GetEntry();

        static void ClearLogs();

        template<typename Function>
        static void DrawLogs(Function f)
        {
            std::lock_guard<std::mutex> lock(mLogMutex);
            for (const auto& log : mLogs) f(log);
        }
    };
}

#endif //CLUTTERENGINE_LOGHISTORY_H