#ifndef CLUTTERENGINE_APPLICATIONEVENT_H
#define CLUTTERENGINE_APPLICATIONEVENT_H
#include <cstdint>
#include <filesystem>
#include "Event.h"

namespace clt
{
    class WindowCloseEvent : public Event
    {
        public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose);
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
    };

    class ProjectLoadEvent : public Event
    {
        std::filesystem::path mPath;
        public:

        explicit ProjectLoadEvent(const std::filesystem::path& path) : mPath(path) {};

        std::filesystem::path GetPath() const { return mPath; }

        EVENT_CLASS_TYPE(ProjectOpen);
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
    };
}

#endif //CLUTTERENGINE_APPLICATIONEVENT_H
