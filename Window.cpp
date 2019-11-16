//
// Created by Kelvin on 16/11/2019.
//

#include <iostream>
#include "Window.h"

using namespace std;

namespace gah {

    Window::Window() : window(NULL), renderer(NULL), texture(NULL), buffer(NULL), blur_buffer(NULL) {}

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
        blur_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

        // Set a value in a memory block
        memset(buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        memset(blur_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

        return true;
    }

    void Window::update() {
        SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    void Window::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

        // When talking about efficiency, this approach is far from being acceptable
        // but for now at least we ensure that we only consider pixels that are
        // within the visible screen.
        if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT) {
            return;
        }

        Uint32 color = 0;

        color += red;
        color <<= 8; // shifts the bits
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF;

        buffer[(y * SCREEN_WIDTH) + x] = color;
    }

    bool Window::handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) { // listen for SDL events
            if (event.type == SDL_QUIT) {
                return false;
            }
        }
        return true;
    }

    void Window::blur() {
        // Swap the buffers
        Uint32 *temp_buffer = buffer;
        buffer = blur_buffer;
        blur_buffer = temp_buffer;

        // Iterate through all the pixels in the screen
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                int red_total = 0;
                int green_total = 0;
                int blue_total = 0;
                /*
                 * 0 0 0
                 * 0 1 0
                 * 0 0 0
                 *
                 * We need to get the pixel located at 1 and make the adjacent
                 * pixels located at 0 have the average color of pixel 1
                 */
                for (int row = -1; row <= 1; row++) {
                    for (int col = -1; col <= 1; col++) {
                        int current_x = x + col;
                        int current_y = y + row;

                        if (current_x >= 0 && current_x < SCREEN_WIDTH &&
                            current_y >= 0 && current_y < SCREEN_HEIGHT) {
                            Uint32 color = blur_buffer[current_y * SCREEN_WIDTH + current_x];
                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;

                            red_total += red;
                            green_total += green;
                            blue_total += blue;
                        }
                    }
                }

                Uint8 red = red_total / 9;
                Uint8 green = green_total / 9;
                Uint8 blue = blue_total / 9;

                setPixel(x, y, red, green, blue);
            }
        }
    }

    void Window::close() {
        // Clear the allocated memory
        delete[] buffer;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(texture);

        // Close and destroy the window
        SDL_DestroyWindow(window);

        // Clean up
        SDL_Quit();
    }
}
