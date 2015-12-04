#ifndef PHYSIC_H
#define PHYSIC_H

#include <QVector>
#include <QDebug>
#include <QThread>
#include <player.h>
#include <Box2D/Box2D.h>
#include "colliderclass.h"



class Physic : public QObject
{
    Q_OBJECT
private :
    b2World _world;
    b2Body* _groundBody[4];
    QVector<Player *> _players;
    QVector<b2Body *> _playersBody;
    ColliderClass myColliderInstance;
public:
    Physic();
    Physic(QVector<Player *> listPlayer);

    void init();
    void initGround();
    void initPlayer();
    void updateDirection();



    QVector<Player *> players() const;
    void setPlayers(const QVector<Player *> &players);
public slots:
    void tick();
};


#endif // PHYSIC_H
