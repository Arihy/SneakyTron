#ifndef TAIL_H
#define TAIL_H

#include <QVector>
#include <QVector3D>
#include "entity.h"


static const int NB_POINTS_INIT=100;

class Tail : public Entity
{
private:
    int _nbChain = NB_POINTS_INIT;
    QVector<QVector3D> _chain;
public:
    Tail();


    EntityType getEntityType() override;
    int size();
    void add(QVector3D);
    QVector<QVector3D> getChain() const;
    void setChain(const QVector<QVector3D> &chain);

};

#endif // TAIL_H
