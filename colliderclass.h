#ifndef COLLIDERCLASS_H
#define COLLIDERCLASS_H

#include "Box2D/Box2D.h"
#include <QDebug>
#include "player.h"

class ColliderClass : public b2ContactListener
{
public:
    ColliderClass();

    virtual void BeginContact(b2Contact *contact) override;
};

#endif // COLLIDERCLASS_H
