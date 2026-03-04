#pragma once

#include <string>
#include <functional>

namespace clt
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory : uint8_t
    {
        None = 0,
        EventCategoryApplication    = (1 << 0),
        EventCategoryInput          = (1 << 1),
        EventCategoryKeyboard       = (1 << 2),
        EventCategoryMouse          = (1 << 3),
        EventCategoryMouseButton    = (1 << 4)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual uint8_t GetCategoryFlags() const override { return category; }

    class Event
    {
        public:
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual uint8_t GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category) const
        {
            return GetCategoryFlags() & static_cast<uint8_t>(category);
        }
    };

    class EventDispatcher
    {
        Event& mEvent;

        template<typename T>
        using EventFunction = std::function<bool(T&)>;

    public:
        explicit EventDispatcher(Event& event) : mEvent(event) {}

        template<typename T>
        bool Dispatch(EventFunction<T> func)
        {
            if (mEvent.GetEventType() == T::GetStaticType())
            {
                mEvent.Handled = func(*static_cast<T*>(&mEvent));
                return true;
            }
            return false;
        }
    };
}