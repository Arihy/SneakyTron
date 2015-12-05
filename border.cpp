#include "border.h"

Border::Border()
{}

Border::Border(QVector2D pos, QVector2D dim)
{
    this->_position = pos;
    this->_dimension = dim;
}

EntityType Border::getEntityType()
{
    return BORDER;
}

QVector2D Border::position() const
{
    return _position;
}

void Border::setPosition(const QVector2D &position)
{
    _position = position;
}

QVector2D Border::dimension() const
{
    return _dimension;
}

void Border::setDimension(const QVector2D &dimension)
{
    _dimension = dimension;
}

