#ifndef PHYSIC_H
#define PHYSIC_H

#include <QVector>
#include <QDebug>
#include <QThread>
#include <player.h>
#include <border.h>
#include <Box2D/Box2D.h>
#include "colliderclass.h"



class Physic : public QObject
{
    Q_OBJECT
private :
    b2World _world;
    QVector<Border *> _borders;
    b2Body* _borderBody[NB_BOUNDARY];
    QVector<Player *> _players;
    QVector<b2Body *> _playersBody;   
    ColliderClass myColliderInstance;
public:
    Physic();
    Physic(QVector<Player *> listPlayer);

    void init();
    void initBorder();
    void initPlayer();
    void updateDirection();



    QVector<Player *> players() const;
    void setPlayers(const QVector<Player *> &players);
    QVector<Border *> borders() const;
    void setBorders(const QVector<Border *> &borders);

public slots:
    void tick();
};


#endif // PHYSIC_H
