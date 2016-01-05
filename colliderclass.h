#ifndef COLLIDERCLASS_H
#define COLLIDERCLASS_H

#include "Box2D/Box2D.h"
#include <QDebug>
#include "player.h"

class ColliderClass : public QObject, public b2ContactListener
{
Q_OBJECT
public:
    ColliderClass();

    virtual void BeginContact(b2Contact *contact) override;
    void CheckPlayerCollision(Entity *bodyUserAData, Entity *bodyUserBData);

signals:
    void playerExplodes(Player*);
};

#endif // COLLIDERCLASS_H
