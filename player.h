#ifndef PLAYER_H
#define PLAYER_H

#include <QVector2D>
#include <QVector4D>
#include <QVector>

class Player
{
private:
    QVector2D _position;
    float _moveSpeed;
    QVector4D _color;
    QVector<QVector2D> _trail;

public:
    Player();
    Player(QVector2D, QVector4D);
};

#endif // PLAYER_H
