#include "particle.h"

Particle::Particle()
{
    std::srand(std::time(0));
    _moveSpeed = MIN_MOVE_SPEED + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX/(MAX_MOVE_SPEED - MIN_MOVE_SPEED)));
    _lifetime = MIN_LIFETIME + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX/(MAX_LIFETIME - MIN_LIFETIME)));
    _position = QVector3D(0.0f, 0.0f, 0.0f);
    _angle = std::rand() % 360 + 1;

    Utils::computeDirection(_angle, _direction);
}

Particle::Particle(QVector3D pos)
{
    std::srand(std::time(0));
    _moveSpeed = MIN_MOVE_SPEED + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX/(MAX_MOVE_SPEED - MIN_MOVE_SPEED)));
    _lifetime = MIN_LIFETIME + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX/(MAX_LIFETIME - MIN_LIFETIME)));
    _position = pos;
    _angle = std::rand() % 360 + 1;

    Utils::computeDirection(_angle, _direction);
}

QVector3D Particle::getPosition()
{
    return _position;
}

float Particle::getlifetime()
{
    return _lifetime;
}

void Particle::update()
{
    _position += _direction * _moveSpeed;
}
