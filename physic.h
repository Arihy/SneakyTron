#ifndef PHYSIC_H
#define PHYSIC_H

#include <QVector>
#include <QDebug>
#include <QThread>
#include <player.h>
#include <Box2D/Box2D.h>


class Physic : public QObject
{
    Q_OBJECT
private :
    b2World _world;
    b2Body* _groundBody;
    QVector<Player *> _players;
    QVector<b2Body *> _playersBody;
public:
    Physic();
    Physic(QVector<Player *> listPlayer);

    void init();
    void gameLoop();



    QVector<Player *> players() const;
    void setPlayers(const QVector<Player *> &players);
public slots:
    void tick();
};


#endif // PHYSIC_H
