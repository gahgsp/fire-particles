//
// Created by Kelvin on 16/11/2019.
//

#ifndef FIRE_PARTICLES_PARTICLES_H
#define FIRE_PARTICLES_PARTICLES_H

#include "Particle.h"

namespace gah {
    class Particles {
    public:
        const static int PARTICLES_NUMBER = 5000;
    public:
        Particles();

        virtual ~Particles();

        const Particle *const getParticles() { return pParticles; };

        void update(int elapsed_time);
    private:
        Particle *pParticles;
        int last_updated;
    };
}

#endif //FIRE_PARTICLES_PARTICLES_H
