//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_INPUT_H
#define PIXLENGINE_INPUT_H

#include "core/KeyCodes.h"
#include "core/MouseCodes.h"
#include "Application.h"

#include <glm/glm.hpp>
#include <glfw/glfw3.h>

enum class CursorMode {
    Visible = GLFW_CURSOR_NORMAL,
    Hidden = GLFW_CURSOR_HIDDEN,
    Captured = GLFW_CURSOR_DISABLED
};

class Input {
public:
    static bool isKeyPressed(KeyCode key);

    static bool isMouseButtonPressed(MouseCode button);

    static void setMousePosition(float x, float y);

    static glm::vec2 getMousePosition();

    static bool isWindowFocused();

    static bool isMouseInWindow();

    static void setCursorMode(CursorMode mode);

    static CursorMode getCursorMode();
};

#endif //PIXLENGINE_INPUT_H
