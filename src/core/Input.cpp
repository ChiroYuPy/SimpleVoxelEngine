//
// Created by ChiroYuki on 26/07/2025.
//

#include "core/Input.h"

#include <GLFW/glfw3.h>

bool Input::isKeyPressed(KeyCode key) {
    auto *window = static_cast<GLFWwindow *>(Application::get().getWindow()->getGLFWWindow());
    auto state = glfwGetKey(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS;
}

bool Input::isMouseButtonPressed(MouseCode button) {
    auto *window = static_cast<GLFWwindow *>(Application::get().getWindow()->getGLFWWindow());
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_PRESS;
}

void Input::setMousePosition(float x, float y) {
    auto *window = static_cast<GLFWwindow *>(Application::get().getWindow()->getGLFWWindow());
    glfwSetCursorPos(window, x, y);
}

glm::vec2 Input::getMousePosition() {
    auto *window = static_cast<GLFWwindow *>(Application::get().getWindow()->getGLFWWindow());
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return {(float) x, (float) y};
}

bool Input::isWindowFocused() {
    auto *window = static_cast<GLFWwindow *>(Application::get().getWindow()->getGLFWWindow());
    return glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
}

bool Input::isMouseInWindow() {
    auto *window = static_cast<GLFWwindow *>(Application::get().getWindow()->getGLFWWindow());
    return glfwGetWindowAttrib(window, GLFW_HOVERED) == GLFW_TRUE;
}

void Input::setCursorMode(CursorMode mode) {
    auto *window = static_cast<GLFWwindow *>(Application::get().getWindow()->getGLFWWindow());
    glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(mode));
}

CursorMode Input::getCursorMode() {
    auto *window = static_cast<GLFWwindow *>(Application::get().getWindow()->getGLFWWindow());
    return static_cast<CursorMode>(glfwGetInputMode(window, GLFW_CURSOR));
}