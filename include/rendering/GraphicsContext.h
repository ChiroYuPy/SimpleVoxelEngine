//
// Created by ChiroYuki on 30/08/2025.
//

#ifndef PIXLENGINE_GRAPHICSCONTEXT_H
#define PIXLENGINE_GRAPHICSCONTEXT_H

#include <string>

// Forward declaration
struct GLFWwindow;
using GLenum = unsigned int;

class GraphicsContext {
public:
    explicit GraphicsContext(GLFWwindow* windowHandle);

    // Non-copyable, non-movable
    GraphicsContext(const GraphicsContext&) = delete;
    GraphicsContext& operator=(const GraphicsContext&) = delete;
    GraphicsContext(GraphicsContext&&) = delete;
    GraphicsContext& operator=(GraphicsContext&&) = delete;

    ~GraphicsContext() = default;

    void Init();
    void SwapBuffers();

private:
    void logOpenGLInfo() const;
    void setupDebugOutput();

    // Helper methods for debug output
    static const char* getDebugSourceString(GLenum source);
    static const char* getDebugTypeString(GLenum type);
    static const char* getDebugSeverityString(GLenum severity);

    GLFWwindow* m_windowHandle;
};

#endif //PIXLENGINE_GRAPHICSCONTEXT_H