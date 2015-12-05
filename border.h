#ifndef BORDER_H
#define BORDER_H

#include "entity.h"
#include <QVector2D>

class Border : public Entity
{
public:
    Border();
    Border(QVector2D pos, QVector2D dim);

    EntityType getEntityType() override;

    QVector2D position() const;
    void setPosition(const QVector2D &position);

    QVector2D dimension() const;
    void setDimension(const QVector2D &dimension);

private:
    QVector2D _position;
    QVector2D _dimension;
};

#endif // BORDER_H
