//
// Created by ChiroYuki on 30/08/2025.
//

#include "rendering/GraphicsContext.h"
#include "core/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
        : m_windowHandle(windowHandle) {
    if (!m_windowHandle) {
        throw std::invalid_argument("Window handle cannot be null");
    }
}

void GraphicsContext::Init() {
    glfwMakeContextCurrent(m_windowHandle);

    // Load OpenGL function pointers
    const int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!gladStatus) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // Log OpenGL information
    logOpenGLInfo();

    // Setup debug output for OpenGL 4.6
    setupDebugOutput();

    Logger::info() << "Graphics context initialized successfully";
}

void GraphicsContext::SwapBuffers() {
    if (m_windowHandle) {
        glfwSwapBuffers(m_windowHandle);
    }
}

void GraphicsContext::logOpenGLInfo() const {
    const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    const char* glslVersion = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

    Logger::info() << "OpenGL Info:";
    Logger::info() << "  Vendor: " << (vendor ? vendor : "Unknown");
    Logger::info() << "  Renderer: " << (renderer ? renderer : "Unknown");
    Logger::info() << "  Version: " << (version ? version : "Unknown");
    Logger::info() << "  GLSL Version: " << (glslVersion ? glslVersion : "Unknown");
}

void GraphicsContext::setupDebugOutput() {
    // OpenGL 4.6 has built-in debug output support
    if (GLAD_GL_VERSION_4_3) { // Debug output available since 4.3
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
                                  GLenum severity, GLsizei length,
                                  const GLchar* message, const void* userParam) {
            // Filter out low priority notifications
            if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
                return;
            }

            const char* sourceStr = getDebugSourceString(source);
            const char* typeStr = getDebugTypeString(type);
            const char* severityStr = getDebugSeverityString(severity);

            // Use appropriate log level based on severity
            if (severity == GL_DEBUG_SEVERITY_HIGH) {
                Logger::error() << "[OpenGL " << severityStr << "] "
                                << sourceStr << " | " << typeStr
                                << " | ID: " << id
                                << " | " << message;
            } else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
                Logger::warn() << "[OpenGL " << severityStr << "] "
                               << sourceStr << " | " << typeStr
                               << " | ID: " << id
                               << " | " << message;
            } else {
                Logger::info() << "[OpenGL " << severityStr << "] "
                               << sourceStr << " | " << typeStr
                               << " | ID: " << id
                               << " | " << message;
            }
        }, nullptr);

        // Set debug message filter (optional - filter out specific messages)
        // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

        Logger::info() << "OpenGL 4.6 debug output enabled";
    } else {
        Logger::warn() << "OpenGL debug output not supported (requires OpenGL 4.3+)";
    }
}

const char* GraphicsContext::getDebugSourceString(GLenum source) {
    switch (source) {
        case GL_DEBUG_SOURCE_API: return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION: return "Application";
        case GL_DEBUG_SOURCE_OTHER: return "Other";
        default: return "Unknown";
    }
}

const char* GraphicsContext::getDebugTypeString(GLenum type) {
    switch (type) {
        case GL_DEBUG_TYPE_ERROR: return "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behavior";
        case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
        case GL_DEBUG_TYPE_MARKER: return "Marker";
        case GL_DEBUG_TYPE_PUSH_GROUP: return "Push Group";
        case GL_DEBUG_TYPE_POP_GROUP: return "Pop Group";
        case GL_DEBUG_TYPE_OTHER: return "Other";
        default: return "Unknown";
    }
}

const char* GraphicsContext::getDebugSeverityString(GLenum severity) {
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH: return "High";
        case GL_DEBUG_SEVERITY_MEDIUM: return "Medium";
        case GL_DEBUG_SEVERITY_LOW: return "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notification";
        default: return "Unknown";
    }
}