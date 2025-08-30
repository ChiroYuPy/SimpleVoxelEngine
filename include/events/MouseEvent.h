//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_MOUSEEVENT_H
#define PIXLENGINE_MOUSEEVENT_H

#include "events/Event.h"
#include "core/MouseCodes.h"

#include <glm/glm.hpp>

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(const float x, const float y)
            : m_MouseX(x), m_MouseY(y) {}

    float getX() const { return m_MouseX; }

    float getY() const { return m_MouseY; }

    glm::vec2 getPosition() const { return {m_MouseX, m_MouseY}; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(const float xOffset, const float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

    float getXOffset() const { return m_XOffset; }

    float getYOffset() const { return m_YOffset; }

    glm::vec2 getOffset() const { return glm::vec2(m_XOffset, m_YOffset); }

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event {
public:
    MouseCode getMouseButton() const { return m_Button; }

    int getMods() const { return m_Mods; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

protected:
    MouseButtonEvent(const MouseCode button, int mods = 0)
            : m_Button(button), m_Mods(mods) {}

    MouseCode m_Button;
    int m_Mods;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(const MouseCode button, int mods = 0)
            : MouseButtonEvent(button, mods) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button << " (mods = " << m_Mods << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(const MouseCode button, int mods = 0)
            : MouseButtonEvent(button, mods) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button << " (mods = " << m_Mods << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

#endif //PIXLENGINE_MOUSEEVENT_H
