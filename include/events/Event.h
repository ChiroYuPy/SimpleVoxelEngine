//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_EVENT_H
#define PIXLENGINE_EVENT_H

#include <iostream>
#include <sstream>

enum class EventType {
    None = 0,
    WindowResize, WindowMoved, WindowClose,
    WindowFocusGained, WindowFocusLost,
    WindowMinimized, WindowMaximized, WindowRestored,
    WindowEnter, WindowLeave,

    AppTick, AppUpdate, AppRender, AppQuit,

    KeyPressed, KeyReleased, KeyTyped,

    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory // bitshift for getting multiple categories
{
    None = 0,
    EventCategoryApplication = 1 << 0,
    EventCategoryWindow = 1 << 1,
    EventCategoryInput = 1 << 2,
    EventCategoryKeyboard = 1 << 3,
    EventCategoryMouse = 1 << 4,
    EventCategoryMouseButton = 1 << 5
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType getEventType() const override { return GetStaticType(); }\
                                virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

class Event {
public:
    virtual ~Event() = default;

    bool Handled = false;

    virtual EventType getEventType() const = 0;

    virtual const char *getName() const = 0;

    virtual int getCategoryFlags() const = 0;

    virtual std::string toString() const { return getName(); }

    bool isInCategory(EventCategory category) {
        return getCategoryFlags() & category;
    }
};

class EventDispatcher {
public:
    EventDispatcher(Event &event)
            : m_Event(event) {
    }

    // F will be deduced by the compiler
    template<typename T, typename F>
    bool dispatch(const F &func) {
        if (m_Event.getEventType() == T::GetStaticType()) {
            m_Event.Handled |= func(static_cast<T &>(m_Event));
            return true;
        }
        return false;
    }

private:
    Event &m_Event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e) {
    return os << e.toString();
}

#endif //PIXLENGINE_EVENT_H
