//
// Created by Kelvin on 16/11/2019.
//

#ifndef FIRE_PARTICLES_PARTICLE_H
#define FIRE_PARTICLES_PARTICLE_H

namespace gah {
    class Particle {
    public:
        double x;
        double y;
        double speed;
        double direction;
    public:
        Particle();

        virtual ~Particle();

        void update(int interval);
    private:
        void init();
    };
}

#endif //FIRE_PARTICLES_PARTICLE_H
