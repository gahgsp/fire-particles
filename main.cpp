#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main() {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "SDL: Fire Particles",           // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            SCREEN_WIDTH,                         // width, in pixels
            SCREEN_HEIGHT,                        // height, in pixels
            SDL_WINDOW_OPENGL               // flag
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        cout << "Could not create window: %s\n" << SDL_GetError() << endl;
        return 1;
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STATIC,
            SCREEN_WIDTH,
            SCREEN_HEIGHT);

    if (renderer == NULL) {
        cout << "Could not create renderer: %s\n" << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (texture == NULL) {
        cout << "Could not create texture: %s\n" << SDL_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Uint32 *buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

    SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    bool quit = false; // flag to leave the program loop
    SDL_Event event;

    while(!quit) {
        // Update the particles
        // Draw the particles
        while(SDL_PollEvent(&event)) { // listen for SDl events
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // Clear the allocated memory
    delete [] buffer;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}