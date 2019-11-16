//
// Created by Kelvin on 16/11/2019.
//

#ifndef FIRE_PARTICLES_WINDOW_H
#define FIRE_PARTICLES_WINDOW_H

#include <SDL2/SDL.h>

namespace gah {
    class Window {
    public:
        const static int SCREEN_WIDTH = 640;
        const static int SCREEN_HEIGHT = 480;
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        Uint32 *buffer;
    public:
        Window();

        bool init();

        void update();

        void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);

        bool handleEvents();

        void clear();

        void close();
    };
}

#endif //FIRE_PARTICLES_WINDOW_H
