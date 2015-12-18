#include "tail.h"

QVector<QVector3D> Tail::getChain() const
{
    return _chain;
}

void Tail::setChain(const QVector<QVector3D> &chain)
{
    _chain = chain;
}

Tail::Tail()
{

}

EntityType Tail::getEntityType()
{
    return TAIL;
}

int Tail::size()
{
    return _chain.size();
}

void Tail::add(QVector3D chain)
{
    _chain.push_back(chain);
    if (_chain.size()>_nbChain) _chain.removeFirst();
}

