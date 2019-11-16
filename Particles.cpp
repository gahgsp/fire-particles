//
// Created by Kelvin on 16/11/2019.
//

#include "Particles.h"

namespace gah {
    Particles::Particles() {
        pParticles = new Particle[PARTICLES_NUMBER];
    }

    Particles::~Particles() {
        delete[] pParticles;
    }

    void Particles::update() {
        for (int i = 0; i < PARTICLES_NUMBER; i++) {
            pParticles[i].update();
        }
    }
}