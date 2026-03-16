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

    public:
        static void AddLog(ConsoleMessage& message);
        static const std::deque<ConsoleMessage>& GetEntry();
        static void ClearLogs();
    };
}

#endif //CLUTTERENGINE_LOGHISTORY_H