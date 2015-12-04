#include "colliderclass.h"

ColliderClass::ColliderClass()
{

}

void ColliderClass::BeginContact(b2Contact *contact)
{
    qDebug()<<"boom !";
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();

}

