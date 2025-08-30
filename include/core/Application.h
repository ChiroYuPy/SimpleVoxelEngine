//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_APPLICATION_H
#define PIXLENGINE_APPLICATION_H

#include <memory>
#include <functional>

#include "Time.h"

// Forward declarations
class Window;
class Renderer;
class InputManager;
class SceneManager;
class Event;
class WindowCloseEvent;
class WindowResizeEvent;

class Application {
public:
    // Singleton pattern
    static Application& get();

    // Non-copyable, non-movable
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    // Core lifecycle
    bool initialize();
    void run();
    void shutdown();
    void onEvent(Event& e);

    // Getters for subsystems
    Window* getWindow() const;
    Renderer* getRenderer() const;
    SceneManager* getSceneManager() const;

    // State queries
    bool isRunning() const;
    void setShouldQuit();

    // Time management
    float getElapsedTime() const;
    float getDeltaTime() const;

private:
    // Private constructor/destructor for singleton
    Application() = default;
    ~Application() = default;

    // Initialization helpers
    bool initGLFW();
    bool initServices();
    void setupEventCallback();

    // Main loop functions
    void update();
    void render();

    // Event handlers
    bool onWindowClose(WindowCloseEvent& e);
    bool onWindowResize(WindowResizeEvent& e);

    // Member variables
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<SceneManager> m_sceneManager;

    bool m_running = false;
    Time m_time;
};

#endif //PIXLENGINE_APPLICATION_H