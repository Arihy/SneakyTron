#ifndef FOOD_H
#define FOOD_H

#include <QVector3D>
#include <QVector4D>

class Food
{
private:
    QVector3D _position;
    float _lifetime;
    float _timer;
    QVector4D _color;

public:
    Food();
    Food(QVector3D position, float lifetime, QVector4D color);

    QVector3D position() const;

    QVector4D color() const;

    float lifetime() const;

    float timer() const;
    void updateTimer();
};

#endif // FOOD_H
