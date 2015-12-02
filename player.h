#ifndef PLAYER_H
#define PLAYER_H

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QVector>
#include <math.h>
#include <QDebug>
#include <QKeyEvent>

#define PI 3.14159265
#define TAIL_LEN_MAX 100

class Player
{
private:
    QVector3D _position;
    float _moveSpeed;
    float _rotationSpeed;
    QVector4D _color;
    QVector<QVector3D> _tail;
    QVector2D _direction;
    bool _rotateLeft;
    bool _rotateRight;
    QVector<Qt::Key> _controller;
    float _angle;

    void rotate();


public:
    Player();
    Player(QVector<Qt::Key>, QVector3D, QVector4D);

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

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // PLAYER_H
