#include "colliderclass.h"

ColliderClass::ColliderClass()
{

}

void ColliderClass::BeginContact(b2Contact *contact)
{

    Entity* bodyUserAData = static_cast<Entity*> (contact->GetFixtureA()->GetBody()->GetUserData());
    Entity* bodyUserBData = static_cast<Entity*> (contact->GetFixtureB()->GetBody()->GetUserData());

    CheckPlayerCollideBorder(bodyUserAData, bodyUserBData);
    CheckPlayerCollideBorder(bodyUserBData, bodyUserAData);
}

void ColliderClass::CheckPlayerCollideBorder(Entity* bodyUserAData, Entity* bodyUserBData)
{
    if((bodyUserAData->getEntityType() == PLAYER && bodyUserBData->getEntityType() == BORDER))
    {
        qDebug() << static_cast<Player*> (bodyUserAData)->getId();
    }
}

