//
// Created by Kelvin on 16/11/2019.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Window.h"

using namespace std;
using namespace gah;

int main() {

    Window window;

    if (!window.init()) {
        cout << "Error initializing SDL" << endl;
    }

    while(true) {
        // Update the particles

        // Draw the particles
        for (int y = 0; y < Window::SCREEN_HEIGHT; y++) {
            for (int x = 0; x < Window::SCREEN_WIDTH; x++) {
                window.setPixel(x, y, 128, 0, 255);
            }
        }

        // Redraw the screen
        window.update();

        // Check for events
        if (!window.handleEvents()) {
            break;
        }
    }

    window.close();

    return 0;
}