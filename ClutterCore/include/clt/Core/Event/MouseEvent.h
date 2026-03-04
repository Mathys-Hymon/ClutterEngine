#pragma once

#include "Event.h"
#include <sstream>

namespace clt
{
    class MouseMovedEvent : public Event
    {
        float mMouseX, mMouseY;

    public:
        MouseMovedEvent(const float x, const float y)
            : mMouseX(x), mMouseY(y) {}

        inline float GetX() const { return mMouseX; }
        inline float GetY() const { return mMouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << mMouseX << ", " << mMouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)
    };

    class MouseScrollEvent : public Event
    {
        float mXOffset, mYOffset;

    public:
        MouseScrollEvent(const float x, const float y)
            : mXOffset(x), mYOffset(y) {}

        inline float GetXOffset() const { return mXOffset; }
        inline float GetYOffset() const { return mYOffset; }


        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrollEvent: " << mXOffset << ", " << mYOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)
    };

    class MouseButtonEvent : public Event
    {
    protected:
        explicit MouseButtonEvent(int button) : mButton(button) {}
        int mButton;

    public:
        inline int GetButton() const { return mButton; }
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput | EventCategory::EventCategoryMouseButton)
    };

    class MouseButtonPressedEvent final : public MouseButtonEvent
    {
        explicit MouseButtonPressedEvent(const int button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << mButton;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent final : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const int button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << mButton;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}