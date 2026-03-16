#ifndef CLUTTERENGINE_IMGUICONSOLESINK_H
#define CLUTTERENGINE_IMGUICONSOLESINK_H

#include "spdlog/sinks/base_sink.h"
#include <Debug/LogHistory.h>

namespace editor::log
{
    class ImGuiConsoleSink : public spdlog::sinks::base_sink<std::mutex>
    {
    public:

        void sink_it_(const spdlog::details::log_msg& msg) override;
        void flush_() override {};
    };

    inline void ImGuiConsoleSink::sink_it_(const spdlog::details::log_msg& msg)
    {
        auto gravity = msg.level;
        spdlog::memory_buf_t formatted;

        formatter_->format(msg,formatted);

        ConsoleMessage message = {formatted.data(), gravity};
        LogHistory::AddLog(message);
    }
}

#endif //CLUTTERENGINE_IMGUICONSOLESINK_H
