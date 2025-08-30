//
// Created by ChiroYuki on 19/07/2025.
//

#include "core/Window.h"
#include "core/Logger.h"
#include "events/WindowEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"

static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char* description) {
    Logger::error() << "GLFW ERROR: " << error << " | " << description;
}

Window::Window(unsigned int width, unsigned int height, const std::string& title) {
    init(width, height, title);
}

Window::~Window() {
    shutdown();
}

void Window::init(unsigned int width, unsigned int height, const std::string& title) {
    m_data.title = title;
    m_data.width = width;
    m_data.height = height;
    m_data.aspectRatio = static_cast<float>(width) / static_cast<float>(std::max(1u, height));
    m_data.verticalSynchronization = true;

    // Initialize GLFW only for the first window
    if (s_GLFWWindowCount == 0) {
        if (!glfwInit()) {
            throw std::runtime_error("GLFW initialization failed");
        }
        glfwSetErrorCallback(GLFWErrorCallback);
    }

    applyHints();

    m_windowHandle = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
                                      m_data.title.c_str(), nullptr, nullptr);
    if (!m_windowHandle) {
        if (s_GLFWWindowCount == 0) {
            glfwTerminate();
        }
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Increment counter AFTER successful window creation
    ++s_GLFWWindowCount;

    m_context = std::make_unique<GraphicsContext>(m_windowHandle);
    m_context->Init();

    glfwSetWindowUserPointer(m_windowHandle, &m_data);
    setVSync(true);

    setupCallbacks();

    Logger::info() << "Window created: " << width << "x" << height << " - '" << title << "'";
}

void Window::shutdown() {
    if (m_windowHandle) {
        glfwDestroyWindow(m_windowHandle);
        m_windowHandle = nullptr;

        --s_GLFWWindowCount;

        if (s_GLFWWindowCount == 0) {
            glfwTerminate();
            Logger::info() << "GLFW terminated";
        }
    }
}

void Window::setupCallbacks() {
    glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data.width = static_cast<unsigned int>(width);
        data.height = static_cast<unsigned int>(height);
        data.aspectRatio = static_cast<float>(width) / static_cast<float>(std::max(1, height));

        WindowResizeEvent event(static_cast<unsigned int>(width),
                                static_cast<unsigned int>(height),
                                data.aspectRatio);
        if (data.eventCallback) {
            data.eventCallback(event);
        }
    });

    glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* window) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        if (data.eventCallback) {
            data.eventCallback(event);
        }
    });

    glfwSetKeyCallback(m_windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(static_cast<KeyCode>(key), 0, mods);
                if (data.eventCallback) {
                    data.eventCallback(event);
                }
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(static_cast<KeyCode>(key), mods);
                if (data.eventCallback) {
                    data.eventCallback(event);
                }
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(static_cast<KeyCode>(key), 1, mods);
                if (data.eventCallback) {
                    data.eventCallback(event);
                }
                break;
            }
        }
    });

    glfwSetCharCallback(m_windowHandle, [](GLFWwindow* window, unsigned int keycode) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        KeyTypedEvent event(keycode);
        if (data.eventCallback) {
            data.eventCallback(event);
        }
    });

    glfwSetMouseButtonCallback(m_windowHandle, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(static_cast<MouseCode>(button), mods);
                if (data.eventCallback) {
                    data.eventCallback(event);
                }
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(static_cast<MouseCode>(button), mods);
                if (data.eventCallback) {
                    data.eventCallback(event);
                }
                break;
            }
        }
    });

    glfwSetScrollCallback(m_windowHandle, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        if (data.eventCallback) {
            data.eventCallback(event);
        }
    });

    glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
        if (data.eventCallback) {
            data.eventCallback(event);
        }
    });

    glfwSetWindowPosCallback(m_windowHandle, [](GLFWwindow* window, int x, int y) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowMovedEvent event(x, y);
        if (data.eventCallback) {
            data.eventCallback(event);
        }
    });

    glfwSetWindowFocusCallback(m_windowHandle, [](GLFWwindow* window, int focused) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (focused) {
            WindowFocusGainedEvent event;
            if (data.eventCallback) {
                data.eventCallback(event);
            }
        } else {
            WindowFocusLostEvent event;
            if (data.eventCallback) {
                data.eventCallback(event);
            }
        }
    });

    glfwSetWindowIconifyCallback(m_windowHandle, [](GLFWwindow* window, int iconified) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (iconified) {
            WindowMinimizedEvent event;
            if (data.eventCallback) {
                data.eventCallback(event);
            }
        } else {
            WindowRestoredEvent event;
            if (data.eventCallback) {
                data.eventCallback(event);
            }
        }
    });

    glfwSetWindowMaximizeCallback(m_windowHandle, [](GLFWwindow* window, int maximized) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (maximized) {
            WindowMaximizedEvent event;
            if (data.eventCallback) {
                data.eventCallback(event);
            }
        } else {
            WindowRestoredEvent event;
            if (data.eventCallback) {
                data.eventCallback(event);
            }
        }
    });

    glfwSetCursorEnterCallback(m_windowHandle, [](GLFWwindow* window, int entered) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (entered) {
            WindowEnterEvent event;
            if (data.eventCallback) {
                data.eventCallback(event);
            }
        } else {
            WindowLeaveEvent event;
            if (data.eventCallback) {
                data.eventCallback(event);
            }
        }
    });
}

void Window::onUpdate() {
    glfwPollEvents();

    if (m_context) {
        m_context->SwapBuffers();
    }
}

void Window::setVSync(bool enabled) {
    if (enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

    m_data.verticalSynchronization = enabled;
}

bool Window::isVSync() const {
    return m_data.verticalSynchronization;
}

void Window::applyHints() {
    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Enable debug context for OpenGL 4.6
#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    // Additional hints for better compatibility
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
}