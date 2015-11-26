#ifndef PLAYER_H
#define PLAYER_H

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QVector>
#include <math.h>
#include <QDebug>

#define PI 3.14159265

class Player
{
private:
    QVector3D _position;
    float _moveSpeed;
    float _rotationSpeed;
    QVector4D _color;
    QVector<QVector3D> _tail;
    QVector2D _direction;
    float _angle;

    void rotate();

public:
    Player();
    Player(QVector3D, QVector4D);

    void move();
    void rotateLeft();
    void rotateRight();
    void updateTail();

    //GETTER & SETTER
    QVector3D position() const;
    void setPosition(const QVector3D &position);
    float moveSpeed() const;
    void setMoveSpeed(float moveSpeed);
    QVector4D color() const;
    void setColor(const QVector4D &color);
    QVector<QVector3D> tail() const;
    void setTail(const QVector<QVector3D> &tail);
};

#endif // PLAYER_H
