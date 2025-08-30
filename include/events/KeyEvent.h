//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_KEYEVENT_H
#define PIXLENGINE_KEYEVENT_H

#include "events/Event.h"
#include "core/KeyCodes.h"

class KeyEvent : public Event {
public:
    KeyCode getKeyCode() const { return m_KeyCode; }

    int getMods() const { return m_Mods; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

protected:
    KeyEvent(const KeyCode keycode, int mods = 0)
            : m_KeyCode(keycode), m_Mods(mods) {}

    KeyCode m_KeyCode;
    int m_Mods;
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(const KeyCode keycode, int repeatCount = 0, int mods = 0)
            : KeyEvent(keycode, mods), m_RepeatCount(repeatCount) {}

    int getRepeatCount() const { return m_RepeatCount; }

    bool isRepeat() const { return m_RepeatCount > 0; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_RepeatCount << ", mods = " << m_Mods << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

private:
    int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(const KeyCode keycode, int mods = 0)
            : KeyEvent(keycode, mods) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode << " (mods = " << m_Mods << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
public:
    KeyTypedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
};

#endif //PIXLENGINE_KEYEVENT_H
