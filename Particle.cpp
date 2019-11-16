//
// Created by Kelvin on 16/11/2019.
//

#include <stdlib.h>
#include <math.h>
#include "Particle.h"

namespace gah {

    Particle::Particle() : x(0), y(0) {
        direction = (2 * M_PI * rand()) / RAND_MAX;
        speed = (0.01 * rand()) / RAND_MAX;
    }

    Particle::~Particle() {

    }

    void Particle::update() {
        double x_speed = speed * cos(direction);
        double y_speed = speed * sin(direction);

        x += x_speed;
        y += y_speed;
    }
}