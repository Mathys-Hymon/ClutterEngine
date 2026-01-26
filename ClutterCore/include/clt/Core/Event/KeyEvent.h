#pragma once
#include "Event.h"

namespace clt
{
    class KeyEvent : public Event
    {
    protected:
        explicit KeyEvent(const int keycode) : mKeyCode(keycode) {}
        int mKeyCode;

    public:
        int GetKeyCode() const { return mKeyCode; }

        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)
    };

    class KeyPressedEvent : public KeyEvent
    {
        int mRepeatCount;

    public:
        KeyPressedEvent(const int keycode, const int repeatCount)
            : KeyEvent(keycode), mRepeatCount(repeatCount) {}

        int GetRepeatCount() const { return mRepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(const int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}