#pragma once

#include <SDL2/SDL.h>

#include <unordered_map>

class Timer {
public:
    float tick();

private:
    double lastTime = 0.0;
};

class Input {
public:
    void beginFrame();
    void setKey(SDL_Keycode key, bool pressed);
    bool isKeyDown(SDL_Keycode key) const;
    void addMouseMotion(float dx, float dy);
    bool isEmpty() const;

    float mouseDeltaX = 0.0f;
    float mouseDeltaY = 0.0f;

private:
    std::unordered_map<SDL_Keycode, bool> keys;
};

class Window {
public:
    const char* title;
    int width;
    int height;

    SDL_Window* sdlWindow = nullptr;
    SDL_GLContext glContext;

    bool changedSize = false;

    Window(const char* title, int width, int height);
    ~Window();

    bool init();
    void pollEvents(Input& input);
    void swapBuffers();
    void cleanup();
    float getAspectRatio() const;
    bool isOpen() const;

private:
    bool running = true;
};
