#include "physic.h"

QVector<Player *> Physic::players() const
{
    return _players;
}

void Physic::setPlayers(const QVector<Player *> &players)
{
    this->_players = players;
}

QVector<Border *> Physic::borders() const
{
    return _borders;
}

void Physic::setBorders(const QVector<Border *> &borders)
{
    _borders = borders;
}

Physic::Physic():_world(b2Vec2(0.0f, 0.0f))
{

}

Physic::Physic(QVector<Player *> listPlayer):_world(b2Vec2(0.0f, 0.0f))
{
    _players=listPlayer;
}

void Physic::init(){
    _world.SetContactListener(&myColliderInstance);
    initBorder();
    initPlayer();
    //initTail();
}

void Physic::initBorder()
{
    b2BodyDef borderBodyDef;
    b2PolygonShape borderBox;
    for (int i=0; i<_borders.size();i++)
    {
        borderBodyDef.position.Set(_borders[i]->position().x(), _borders[i]->position().y());
        borderBodyDef.type = b2_staticBody;
        _borderBody[i] = _world.CreateBody(&borderBodyDef);
        borderBox.SetAsBox(_borders[i]->dimension().x(), _borders[i]->dimension().y());
        qDebug()<<"position  : "<<_borders[i]->position()<<" hald-dim : "<<_borders[i]->dimension();
        _borderBody[i]->CreateFixture(&borderBox, 1.0f);
        _borderBody[i]->SetUserData(_borders[i]);
    }
}

void Physic::initPlayer()
{
    b2CircleShape playerShape;
    playerShape.m_p.Set(0, 0); //position, relative to body position
    playerShape.m_radius = PLAYER_RADIUS; // radius

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape=&playerShape;
    playerFixtureDef.density=0;

    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;

    _playersBody.clear();
    for (int i=0 ;i <_players.size();i++)
    {
        playerBodyDef.position.Set( _players[i]->position().x()  ,_players[i]->position().y());
        _playersBody<<_world.CreateBody(&playerBodyDef);
        _playersBody[i]->CreateFixture(&playerFixtureDef);
        _playersBody[i]->SetUserData( _players[i]); // Bind du body avec l'objet player
    }
}


void Physic::initTail(){
    b2BodyDef tailBodyDef;
    tailBodyDef.type = b2_staticBody;
    b2ChainShape tailLine;
    QVector< b2Vec2> vec;
    for(Player* player : _players)
    {
        vec.clear();
        vec.push_back(b2Vec2(player->position().x(), player->position().y()));
        vec.push_back(b2Vec2(player->position().x(), player->position().y()-PLAYER_RADIUS));
//        for (const QVector3D v : player->tail()->getChain())
//            vec.push_back(b2Vec2(v.x(),v.y()));
        tailLine.CreateChain(vec.constData(),(int32) vec.size());
        _tailsBody<<_world.CreateBody(&tailBodyDef);
        _tailsBody.last()->CreateFixture(&tailLine,1.0f);
        _tailsBody.last()->SetUserData(player->tail());
    }




    //vec.clear();
//    for (int i =0;i<2;i++)
//        vec.push_back(b2Vec2(1.0*i, 0.0f));

//    tailLine.CreateChain(vec.constData(),(int32) vec.size());
//    _tailsBody<<_world.CreateBody(&tailBodyDef);
//    _tailsBody.last()->CreateFixture(&tailLine,1.0f);
//    b2ChainShape *chainShape = (b2ChainShape*) _tailsBody.last()->GetFixtureList()[0].GetShape();
//    qDebug()<<"body created";
//    for (int i = 0;i<2;i++)
//        qDebug()<<"vertice "<<i<<" x : "<<chainShape->m_vertices[i].x<<" , y : "<<chainShape->m_vertices[i].y;
//    _tailsBody.last()->SetUserData(_players[0]->tail());
}
void Physic::updateTail()
{
    b2BodyDef tailBodyDef;
    tailBodyDef.type = b2_staticBody;
    b2ChainShape tailLine;
    QVector< b2Vec2> vec;
    for(Player* player : _players)
    {
        vec.clear();
        vec.push_back(b2Vec2(player->position().x(), player->position().y()));
        for (const QVector3D v : player->tail()->getChain())
            vec.push_back(b2Vec2(v.x(),v.y()));
        tailLine.CreateChain(vec.constData(),(int32) vec.size());
        _tailsBody<<_world.CreateBody(&tailBodyDef);
        _tailsBody.last()->CreateFixture(&tailLine,1.0f);
    }
    qDebug()<<_tailsBody.last()->GetFixtureList()[0].GetShape()->m_type;
}

void Physic::updateDirection()
{
    for(Player* player : _players)
    {
        player->computeDirection();
    }
}

void Physic::tick()
{
    float32 timeStep = 30.0f/1000.0f;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    updateDirection();

    for (int i=0 ;i <_players.size();i++)
    {
        _playersBody[i]->SetLinearVelocity(10*b2Vec2(_players[i]->direction().x()*_players[i]->moveSpeed(),_players[i]->direction().y()*_players[i]->moveSpeed()));
    }
    _world.Step(timeStep, velocityIterations, positionIterations);

    for (int i=0 ;i <_players.size();i++)
    {
        b2Vec2 position = _playersBody[i]->GetPosition();
        _players[i]->setPosition(QVector3D(position.x, position.y, 0));
    }

}
