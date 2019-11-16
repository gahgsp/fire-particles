//
// Created by Kelvin on 16/11/2019.
//

#include <stdlib.h>
#include <math.h>
#include "Particle.h"

namespace gah {

    Particle::Particle() {
        init();
    }

    Particle::~Particle() {}

    void Particle::init() {
        x = 0;
        y = 0;

        direction = (2 * M_PI * rand()) / RAND_MAX;
        speed = (0.04 * rand()) / RAND_MAX;

        speed *= speed;
    }

    void Particle::update(int interval) {
        direction += interval * 0.0005;

        double x_speed = speed * cos(direction);
        double y_speed = speed * sin(direction);

        x += x_speed * interval;
        y += y_speed * interval;

        // If a particle goes off the screen
        // we reinitialize it
        if (x < -1 || x > 1 || y < -1 || y > 1) {
            init();
        }

        // Just a tweak to make the explosion seems more fancy
        if (rand() < RAND_MAX/100) {
            init();
        }
    }
}