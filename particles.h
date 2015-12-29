#ifndef PARTICLES_H
#define PARTICLES_H

#include <QVector4D>
#include <QVector>
#include "particle.h"

const int NB_PARTICLES = 10;

class Particles
{
private:
    QVector<Particle> _particles;
    QVector4D _color;

    float _timer;

public:
    Particles();
    Particles(QVector4D color);
    void initParticles(QVector3D pos);

    QVector<QVector3D> getParticlesPosition();

    void update();
};

#endif // PARTICLES_H
