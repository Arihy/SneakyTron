#ifndef PLAYER_H
#define PLAYER_H

#include <QVector3D>
#include <QVector4D>
#include <QVector>

class Player
{
private:
    QVector3D _position;
    float _moveSpeed;
    QVector3D _color;
    QVector<QVector3D> _trail;

public:
    Player();
    Player(QVector3D, QVector3D);

    QVector3D position() const;
    void setPosition(const QVector3D &position);
    float moveSpeed() const;
    void setMoveSpeed(float moveSpeed);
    QVector3D color() const;
    void setColor(const QVector3D &color);
    QVector<QVector3D> trail() const;
    void setTrail(const QVector<QVector3D> &trail);
};

#endif // PLAYER_H
