#include "player.h"

Player::Player()
{
}

Player::Player(QVector3D position, QVector4D color)
{
    _position = position;
    _color = color;
    _moveSpeed = 0.01f;
}

void Player::move()
{
    float newPosition = _position.y() + _moveSpeed;
    _position.setY(newPosition);
}

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

QVector4D Player::color() const
{
    return _color;
}

void Player::setColor(const QVector4D &color)
{
    _color = color;
}

QVector<QVector3D> Player::tail() const
{
    return _tail;
}

void Player::setTail(const QVector<QVector3D> &tail)
{
    _tail = trail;
}

void Player::updateTail()
{
    _tail.push_back(_position);
}

