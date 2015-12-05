#ifndef ENTITY_H
#define ENTITY_H

enum EntityType {PLAYER = 1, BORDER =2, BONUS = 3};

class Entity
{
public:
    Entity();

    virtual EntityType getEntityType();
};

#endif // ENTITY_H
