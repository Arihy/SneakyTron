#include "player.h"

QVector3D Player::position() const
{
    return _position;
}

void Player::setPosition(const QVector3D &position)
{
    _position = position;
}

float Player::moveSpeed() const
{
    return _moveSpeed;
}

void Player::setMoveSpeed(float moveSpeed)
{
    _moveSpeed = moveSpeed;
}

QVector3D Player::color() const
{
    return _color;
}

void Player::setColor(const QVector3D &color)
{
    _color = color;
}

QVector<QVector3D> Player::trail() const
{
    return _trail;
}

void Player::setTrail(const QVector<QVector3D> &trail)
{
    _trail = trail;
}

Player::Player()
{
}

Player::Player(QVector3D position, QVector3D color)
{
    _position = position;
    _color = color;
}

