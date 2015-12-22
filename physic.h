#ifndef PHYSIC_H
#define PHYSIC_H

#include <QVector>
#include <QDebug>
#include <QThread>
#include <player.h>
#include <border.h>
#include <Box2D/Box2D.h>
#include "colliderclass.h"

const float PLAYER_RADIUS=0.01;

class Physic : public QObject
{
    Q_OBJECT
private :
    b2World _world;
    QVector<Border *> _borders;
    b2Body* _borderBody[NB_BOUNDARY];
    QVector<Player *> _players;
    QVector<b2Body *> _playersBody;
    QVector<b2Body *> _tailsBody;
    ColliderClass myColliderInstance;
public:
    Physic();
    Physic(QVector<Player *> listPlayer);

    void init();
    void initBorder();
    void initPlayer();
    void initTail();
    void updateTail();
    void updateDirection();



    QVector<Player *> players() const;
    void setPlayers(const QVector<Player *> &players);
    QVector<Border *> borders() const;
    void setBorders(const QVector<Border *> &borders);

public slots:
    void tick();
};


#endif // PHYSIC_H
