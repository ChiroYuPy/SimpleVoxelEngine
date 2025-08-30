//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_WINDOWEVENT_H
#define PIXLENGINE_WINDOWEVENT_H

#include "Event.h"

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int width, unsigned int height, float aspectRatio)
            : m_width(width), m_height(height), m_aspectRatio(aspectRatio) {}

    unsigned int getWidth() const { return m_width; }

    unsigned int getHeight() const { return m_height; }

    float getAspectRatio() const { return m_aspectRatio; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: (width=" << m_width << ") (height=" << m_height << ") (aspectRatio="
           << m_aspectRatio << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
    unsigned int m_width, m_height;
    float m_aspectRatio;
};

class WindowMovedEvent : public Event {
public:
    WindowMovedEvent(int x, int y) : m_x(x), m_y(y) {}

    int getX() const { return m_x; }

    int getY() const { return m_y; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "WindowMovedEvent: (x=" << m_x << ") (y=" << m_y << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowMoved)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
    int m_x, m_y;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowFocusGainedEvent : public Event {
public:
    WindowFocusGainedEvent() = default;

    EVENT_CLASS_TYPE(WindowFocusGained)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowFocusLostEvent : public Event {
public:
    WindowFocusLostEvent() = default;

    EVENT_CLASS_TYPE(WindowFocusLost)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowMinimizedEvent : public Event {
public:
    WindowMinimizedEvent() = default;

    EVENT_CLASS_TYPE(WindowMinimized)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowMaximizedEvent : public Event {
public:
    WindowMaximizedEvent() = default;

    EVENT_CLASS_TYPE(WindowMaximized)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowRestoredEvent : public Event {
public:
    WindowRestoredEvent() = default;

    EVENT_CLASS_TYPE(WindowRestored)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowEnterEvent : public Event {
public:
    WindowEnterEvent() = default;

    EVENT_CLASS_TYPE(WindowEnter)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowLeaveEvent : public Event {
public:
    WindowLeaveEvent() = default;

    EVENT_CLASS_TYPE(WindowLeave)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

#endif //PIXLENGINE_WINDOWEVENT_H
