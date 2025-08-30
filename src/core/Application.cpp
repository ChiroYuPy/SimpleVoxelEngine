//
// Created by ChiroYuki on 19/07/2025.
//

#include "core/Application.h"
#include "core/Window.h"
#include "core/Logger.h"

#include "rendering/OpenGL/RenderAPI.h"
#include "rendering/Renderer.h"
#include "scene/SceneManager.h"
#include "events/WindowEvent.h"

Application& Application::get() {
    static Application instance;
    return instance;
}

bool Application::initialize() {
    if (!initGLFW()) {
        Logger::error() << "Failed to initialize GLFW";
        return false;
    }

    try {
        m_window = std::make_unique<Window>(1280, 720, "Pixl Engine");
    } catch (const std::exception& e) {
        Logger::error() << "Failed to create window: " << e.what();
        return false;
    }

    if (!initServices()) {
        Logger::error() << "Failed to initialize services";
        return false;
    }

    setupEventCallback();

    m_time.start();
    m_running = true;

    // Trigger initial resize event
    WindowResizeEvent resizeEvent(m_window->getWidth(), m_window->getHeight(), m_window->getAspectRatio());
    onEvent(resizeEvent);

    Logger::info() << "Application initialized successfully";
    return true;
}

bool Application::initGLFW() {
    if (!glfwInit()) {
        return false;
    }
    return true;
}

bool Application::initServices() {
    // ------------ [ Renderer ] ------------ //
    m_renderer = std::make_unique<Renderer>();
    if (!m_renderer->initialize()) {
        return false;
    }

    // ------------ [ SceneManager ] ------------ //
    m_sceneManager = std::make_unique<SceneManager>();

    return true;
}

void Application::setupEventCallback() {
    m_window->setEventCallback([this](Event& e) {
        onEvent(e);
    });
}

void Application::onEvent(Event& e) {
    // Create event dispatcher to handle events properly
    switch (e.getEventType()) {
        case EventType::WindowClose: {
            WindowCloseEvent& closeEvent = static_cast<WindowCloseEvent&>(e);
            onWindowClose(closeEvent);
            break;
        }
        case EventType::WindowResize: {
            WindowResizeEvent& resizeEvent = static_cast<WindowResizeEvent&>(e);
            onWindowResize(resizeEvent);
            break;
        }
        default:
            break;
    }
}

void Application::run() {
    Logger::info() << "Starting main loop";

    while (m_running && m_window && !glfwWindowShouldClose(m_window->getNativeWindow())) {

        m_time.update();

        RenderAPI::Clear();

        update();
        render();

        m_window->onUpdate();
    }

    Logger::info() << "Main loop ended";
}

void Application::update() {
    const float deltaTime = getDeltaTime();

    if (m_sceneManager) {
        m_sceneManager->update(deltaTime);
    }
}

void Application::render() {
    if (!m_renderer) {
        Logger::warn() << "Renderer is null, skipping render";
        return;
    }

    if (m_sceneManager) {
        m_sceneManager->render();
    }
}

void Application::shutdown() {
    Logger::info() << "Shutting down application";

    m_running = false;

    // Shutdown in reverse order of initialization
    if (m_sceneManager) {
        m_sceneManager.reset();
    }

    if (m_renderer) {
        m_renderer.reset();
    }

    if (m_window) {
        m_window.reset();
    }

    // GLFW will be terminated by Window destructor when last window is destroyed
}

// Getters
Window* Application::getWindow() const {
    return m_window.get();
}

Renderer* Application::getRenderer() const {
    return m_renderer.get();
}

SceneManager* Application::getSceneManager() const {
    return m_sceneManager.get();
}

bool Application::isRunning() const {
    return m_running;
}

void Application::setShouldQuit() {
    m_running = false;
    Logger::info() << "Application quit requested";
}

float Application::getElapsedTime() const {
    return m_time.getElapsedTime();
}

float Application::getDeltaTime() const {
    return m_time.getDeltaTime();
}

// Event handlers
bool Application::onWindowClose(WindowCloseEvent& e) {
    Logger::info() << "Window close event received";
    m_running = false;
    return true; // Event handled
}

bool Application::onWindowResize(WindowResizeEvent& e) {
    const int width = e.getWidth();
    const int height = e.getHeight();

    Logger::info() << "Window resized to: " << width << "x" << height;

    if (width <= 0 || height <= 0) {
        Logger::warn() << "Invalid resize dimensions, ignoring";
        return true;
    }

    RenderAPI::SetViewport(0, 0, width, height);

    // Forward to renderer if it has a resize method
    if (m_renderer) {
        // m_renderer->onWindowResize(width, height); // Uncomment if this method exists
    }

    return true; // Event handled
}