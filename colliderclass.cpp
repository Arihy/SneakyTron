#include "colliderclass.h"

ColliderClass::ColliderClass()
{

}

void ColliderClass::BeginContact(b2Contact *contact)
{

    Entity* bodyUserAData = static_cast<Entity*> (contact->GetFixtureA()->GetBody()->GetUserData());
    Entity* bodyUserBData = static_cast<Entity*> (contact->GetFixtureB()->GetBody()->GetUserData());

    if (bodyUserAData->getEntityType() == PLAYER)
        qDebug()<<"boom !";

    if (bodyUserBData->getEntityType() == PLAYER)
        qDebug()<<"boom !";
}

