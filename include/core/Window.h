//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_WINDOW_H
#define PIXLENGINE_WINDOW_H

#include "events/Event.h"
#include "GLT.h"
#include "rendering/GraphicsContext.h"

#include <string>
#include <functional>
#include <memory>

class Window {
public:
    using EventCallbackFunction = std::function<void(Event&)>;

    Window(unsigned int width, unsigned int height, const std::string& title);
    ~Window();

    // Non-copyable, non-movable
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    void onUpdate();

    // Getters
    uint32_t getWidth() const { return m_data.width; }
    uint32_t getHeight() const { return m_data.height; }
    float getAspectRatio() const { return m_data.aspectRatio; }
    GLFWwindow* getNativeWindow() const { return m_windowHandle; }

    // Window state
    bool shouldClose() const { return glfwWindowShouldClose(m_windowHandle); }

    // Event system
    void setEventCallback(const EventCallbackFunction& callback) {
        m_data.eventCallback = callback;
    }

    // VSync control
    void setVSync(bool enabled);
    bool isVSync() const;

private:
    void init(unsigned int width, unsigned int height, const std::string& title);
    void shutdown();
    void setupCallbacks();
    void applyHints();

    GLFWwindow* m_windowHandle = nullptr;
    std::unique_ptr<GraphicsContext> m_context;

    struct WindowData {
        std::string title;
        unsigned int width = 0;
        unsigned int height = 0;
        float aspectRatio = 1.0f;
        bool verticalSynchronization = true;

        EventCallbackFunction eventCallback;
    };

    WindowData m_data;
};

#endif //PIXLENGINE_WINDOW_H