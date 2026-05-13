#include <SimpleGL/window.h>

#include "glad/glad.h"
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <cmath>

Window::Window(const char* title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;
}

bool Window::init() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }

    // Request OpenGL 4.1 Core Profile.
    // On macOS, 4.1 is the max supported OpenGL version.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Optional but useful
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // anti-aliasing
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    sdlWindow = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN_DESKTOP
    );

    if (!sdlWindow) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    glContext = SDL_GL_CreateContext(sdlWindow);

    if (!glContext) {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return false;
    }

    SDL_GL_MakeCurrent(sdlWindow, glContext);

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return false;
    }

    // make full use of mac retina display
    int drawableWidth;
    int drawableHeight;
    SDL_GL_GetDrawableSize(sdlWindow, &drawableWidth, &drawableHeight);
    glViewport(0, 0, drawableWidth, drawableHeight);

    SDL_GL_SetSwapInterval(1); // vsync

    SDL_SetRelativeMouseMode(SDL_TRUE); // makes it so mouse doesn't go off window

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(sdlWindow, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");

    return true;
}

Window::~Window() {
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}

float Window::getAspectRatio() const {
    int drawableWidth;
    int drawableHeight;
    SDL_GL_GetDrawableSize(sdlWindow, &drawableWidth, &drawableHeight);
    
    return static_cast<float>(drawableWidth) / static_cast<float>(drawableHeight);
}

bool Window::isOpen() const {
    return running;
}

void Window::pollEvents(Input& input) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);

        if (event.type == SDL_QUIT) {
            running = false;
        }

        if (event.type == SDL_KEYDOWN) {
            input.setKey(event.key.keysym.sym, true);

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }

            // if (event.key.keysym.sym == SDLK_TAB) {
            //     if (SDL_GetRelativeMouseMode() == SDL_TRUE) {
            //         SDL_SetRelativeMouseMode(SDL_FALSE);
            //     } else {
            //         SDL_SetRelativeMouseMode(SDL_TRUE);
            //     }
            // }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            // swap from relative mouse mode to editing gui
            if (event.button.button == SDL_BUTTON_RIGHT) {
                if (SDL_GetRelativeMouseMode() == SDL_TRUE) {
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                } else {
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                }
            }
        }

        if (event.type == SDL_KEYUP) {
            input.setKey(event.key.keysym.sym, false);
        }

        if (event.type == SDL_MOUSEMOTION) {
            input.addMouseMotion(
                static_cast<float>(event.motion.xrel),
                static_cast<float>(event.motion.yrel)
            );
        }

        if (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_RESIZED) {
            int drawableWidth;
            int drawableHeight;
            SDL_GL_GetDrawableSize(sdlWindow, &drawableWidth, &drawableHeight);
            glViewport(0, 0, drawableWidth, drawableHeight);
            changedSize = true;
        }
    }
}

void Window::swapBuffers() {
    SDL_GL_SwapWindow(sdlWindow);
}

void Window::cleanup() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}


void Input::beginFrame() {
    mouseDeltaX = 0.0f;
    mouseDeltaY = 0.0f;
}

void Input::setKey(SDL_Keycode key, bool pressed) {
    keys[key] = pressed;
}

bool Input::isKeyDown(SDL_Keycode key) const {
    auto it = keys.find(key);
    return it != keys.end() && it->second;
}

void Input::addMouseMotion(float dx, float dy) {
    mouseDeltaX += dx;
    mouseDeltaY += dy;
}

bool Input::isEmpty() const {
    return keys.empty();
}


float Timer::tick() {
    double currentTime = static_cast<double>(SDL_GetPerformanceCounter());

    double frequency = static_cast<double>(SDL_GetPerformanceFrequency());

    double timeSeconds = currentTime / frequency;

    float deltaTime = static_cast<float>(timeSeconds - lastTime);

    lastTime = timeSeconds;

    return deltaTime;
}
