#include "particles.h"

Particles::Particles()
{
    _timer = 0.0f;
    _color = QVector4D(1.0f, 0.0f, 0.0f, 1.0f);
}

Particles::Particles(QVector4D color)
{
    _timer = 0.0f;
    _color = color;
}

void Particles::initParticles(QVector3D pos)
{
    _timer = 0.0f;
    _particles.clear();
    for(int i = 0; i < NB_PARTICLES; i++)
    {
        _particles.push_back(Particle(pos));
    }
}

QVector<QVector3D> Particles::getParticlesPosition()
{
    QVector<QVector3D> particlesPosition = QVector<QVector3D>();
    for(Particle p : _particles)
    {
        particlesPosition.push_back(p.getPosition());
    }
    return particlesPosition;
}

void Particles::update()
{
    for(int i = 0; i < _particles.size(); i++)
    {
        if(_timer > _particles[i].getlifetime())
        {
            _particles.remove(i);
        }
        else
        {
            _particles[i].update();
        }
    }
}
