#include "physic.h"

Physic::Physic()
{
}

Physic::Physic(QVector<Player *> listPlayer)
{
    _players=listPlayer;
}

void Physic::init(){
    // On crée le world avec une gravity nulle

    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

}
