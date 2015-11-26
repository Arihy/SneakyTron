#include "player.h"

Player::Player()
{
}

Player::Player(QVector3D position, QVector4D color)
{
    _position = position;
    _color = color;
    _moveSpeed = 0.01f;
    _rotationSpeed = 10;
    _direction = QVector2D(0, 1);
    _angle = 0;
}

void Player::move()
{
    _position += _direction * _moveSpeed;
}

void Player::rotate()
{
    float angle = (_angle * PI) / 180.0;
    QVector2D direction = _direction;
    _direction.setX((direction.x() * cos(angle)) - (direction.y() * sin(angle)));
    _direction.setY((direction.x() * sin(angle)) + (direction.y() * cos(angle)));
}

void Player::rotateRight()
{
    _angle = -_rotationSpeed;
    rotate();
}

void Player::rotateLeft()
{
    _angle = +_rotationSpeed;
    rotate();
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
    _tail = tail;
}

void Player::updateTail()
{
    _tail.push_back(_position);
}

