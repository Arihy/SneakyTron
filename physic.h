#ifndef PHYSIC_H
#define PHYSIC_H

#include <QVector>
#include <player.h>
#include <Box2D/Box2D.h>


class Physic
{
private :
    QVector<Player *> _players;
public:
    Physic();
    Physic(QVector<Player *> listPlayer);

    void init();
};

#endif // PHYSIC_H
