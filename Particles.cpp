//
// Created by Kelvin on 16/11/2019.
//

#include "Particles.h"

namespace gah {
    Particles::Particles(): last_updated(0) {
        pParticles = new Particle[PARTICLES_NUMBER];
    }

    Particles::~Particles() {
        delete[] pParticles;
    }

    void Particles::update(int elapsed_time) {
        int interval = elapsed_time - last_updated;

        for (int i = 0; i < PARTICLES_NUMBER; i++) {
            pParticles[i].update(interval);
        }

        last_updated = elapsed_time;
    }
}