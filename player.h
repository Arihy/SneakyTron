#ifndef PLAYER_H
#define PLAYER_H

#include <QVector2D>
#include <QVector4D>
#include <QVector>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui>

class Player
{
private:
    QVector3D _position;
    float _moveSpeed;
    QVector4D _color;
    QVector<QVector2D> _trail;





public:
    Player();
    Player(QVector3D, QVector4D);
    void initialize();





    QVector3D position() const;
    void setPosition(const QVector3D &position);
    float moveSpeed() const;
    void setMoveSpeed(float moveSpeed);
    QVector4D color() const;
    void setColor(const QVector4D &color);
    QVector<QVector2D> trail() const;
    void setTrail(const QVector<QVector2D> &trail);
};

#endif // PLAYER_H
