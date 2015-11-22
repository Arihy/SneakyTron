#ifndef PLAYER_H
#define PLAYER_H

#include <QVector3D>
#include <QVector>

class Player
{
private:
    QVector3D _position;
    float _moveSpeed;
    QVector4D _color;
    QVector<QVector3D> _tail;

public:
    Player();
    Player(QVector3D, QVector4D);

    void move();
    void updateTail();

    //GETTER & SETTER
    QVector3D position() const;
    void setPosition(const QVector3D &position);
    float moveSpeed() const;
    void setMoveSpeed(float moveSpeed);
    QVector4D color() const;
    void setColor(const QVector4D &color);
    QVector<QVector3D> tail() const;
    void setTrail(const QVector<QVector3D> &tail);
};

#endif // PLAYER_H
