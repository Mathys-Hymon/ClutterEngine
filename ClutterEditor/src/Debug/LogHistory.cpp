#include <Debug/LogHistory.h>

std::deque<editor::log::ConsoleMessage> editor::log::LogHistory::mLogs;
std::mutex editor::log::LogHistory::mLogMutex;

void editor::log::LogHistory::AddLog(ConsoleMessage& message)
{
    std::lock_guard<std::mutex> lock(mLogMutex);

    if (mLogs.size() >= 1000) mLogs.pop_front();
    mLogs.emplace_back(std::move(message));
}

const std::deque<editor::log::ConsoleMessage>& editor::log::LogHistory::GetEntry()
{
    return mLogs;
}

void editor::log::LogHistory::ClearLogs()
{
    std::lock_guard<std::mutex> lock(mLogMutex);
    mLogs.clear();
}
