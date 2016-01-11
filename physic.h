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
    Border *_border;
    b2Body* _borderBody;
    QVector<Player *> _players;
    QVector<b2Body *> _playersBody;
    QVector<b2Body *> _tailsBody;
    ColliderClass myColliderInstance;
    QVector<b2Body *> _binBodies;
    bool pause = false;
public:
    Physic();
    Physic(QVector<Player *> listPlayer);

    void init();
    void initBorder();
    void initPlayer();
    void initTail();
    void updateTail();
    void updateDirection();
    void addToBin(b2Body *body);
    void resetWorldContent();



    QVector<Player *> players() const;
    void setPlayers(const QVector<Player *> &players);
    ColliderClass* getMyColliderInstance();
    b2World* getWorld() ;
    Border *getBorder() const;
    void setBorder(Border *border);

public slots:
    void tick();

};


#endif // PHYSIC_H
