#ifndef CLUTTERENGINE_APPLICATIONEVENT_H
#define CLUTTERENGINE_APPLICATIONEVENT_H
#include <cstdint>

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
}

#endif //CLUTTERENGINE_APPLICATIONEVENT_H
