//
// Created by Kelvin on 16/11/2019.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "Window.h"
#include "Particles.h"

using namespace std;
using namespace gah;

int main() {

    srand(time(NULL));

    Window window;

    if (!window.init()) {
        cout << "Error initializing SDL" << endl;
    }

    Particles particles;

    while (true) {
        // Update the particles

        int elapsed_time = SDL_GetTicks();

        window.clear();
        particles.update(elapsed_time);

        unsigned char red = (unsigned char) ((1 + sin(elapsed_time * 0.0001)) * 128);
        unsigned char green = (unsigned char) ((1 + sin(elapsed_time * 0.0002)) * 128);
        unsigned char blue = (unsigned char) ((1 + sin(elapsed_time * 0.0003)) * 128);

        // Create the particles
        const Particle *const pParticles = particles.getParticles();
        for (int i = 0; i < Particles::PARTICLES_NUMBER; i++) {
            Particle particle = pParticles[i];

            int x = (particle.x + 1) * (Window::SCREEN_WIDTH / 2);
            int y = particle.y * (Window::SCREEN_WIDTH / 2) + (Window::SCREEN_HEIGHT / 2);

            window.setPixel(x, y, red, green, blue);
        }

        // Draw the screen
        window.update();

        // Check for events
        if (!window.handleEvents()) {
            break;
        }
    }

    window.close();

    return 0;
}