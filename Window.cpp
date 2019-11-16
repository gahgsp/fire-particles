//
// Created by Kelvin on 16/11/2019.
//

#include <iostream>
#include "Window.h"

using namespace std;

namespace gah {
Window::Window(): window(NULL), renderer(NULL), texture(NULL), buffer(NULL) {

}

bool Window::init() {

    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "SDL: Fire Particles", // window title
            SDL_WINDOWPOS_UNDEFINED, // initial x position
            SDL_WINDOWPOS_UNDEFINED, // initial y position
            SCREEN_WIDTH,               // width, in pixels
            SCREEN_HEIGHT,              // height, in pixels
            SDL_WINDOW_OPENGL);   // flag

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        cout << "Could not create window: %s\n" << SDL_GetError() << endl;
        return false;
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STATIC,
            SCREEN_WIDTH,
            SCREEN_HEIGHT);

    if (renderer == NULL) {
        cout << "Could not create renderer: %s\n" << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (texture == NULL) {
        cout << "Could not create texture: %s\n" << SDL_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    // This buffer represents all the pixels in the screen
    buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

    // Set a value in a memory block
    memset(buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        buffer[i] = 0xFF0000FF;
    }

    return true;
}

void Window::update() {
    SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Window::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
    Uint32 color = 0;

    color += red;
    color <<= 8; // shifts the byte
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    buffer[(y * SCREEN_WIDTH) + x] = color;
}

bool Window::handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) { // listen for SDl events
        if (event.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

void Window::close() {
    // Clear the allocated memory
    delete [] buffer;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
}
}
