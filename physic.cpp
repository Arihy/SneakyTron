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

ColliderClass* Physic::getMyColliderInstance()
{
    return &myColliderInstance;
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
    initTail();
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
    for(Player* player : _players)
    {
        _tailsBody<<_world.CreateBody(&tailBodyDef);
        _tailsBody.last()->SetUserData(player->tail());
    }


}

void Physic::updateTail()
{
    static const float minDistance=0.006;
    QVector3D memory;
    std::vector< b2Vec2> vec;
    QVector<QVector3D> tmp, tmp2;
    Tail* tail;
    for(b2Body * body : _tailsBody)
    {
        b2Fixture *fixtureA = body->GetFixtureList();
        if (fixtureA!=NULL) body->DestroyFixture(fixtureA);
        tmp.clear();
        tmp2.clear();
        tail=static_cast<Tail*> (body->GetUserData());
        tmp = tail->getChain();
        vec.clear();
        for (QVector3D v : tmp)
            if (v.distanceToPoint(tmp.last())>PLAYER_RADIUS) tmp2.push_back(v);
        if (tmp2.size()<=2) break;
        vec.push_back(b2Vec2(tmp2[0].x(),tmp2[0].y()));
        memory=tmp2[0];
        for (int i = 1;i<tmp2.size();i++){
            if (tmp2[i].distanceToPoint(memory)<minDistance) continue;
            memory=tmp2[i];
            vec.push_back(b2Vec2(tmp2[i].x(),tmp2[i].y()));
        }
        if (vec.size()<2) continue; // Il faut au moins 2 points pour créer une chaine
        b2ChainShape chain;
        chain.CreateChain(&vec[0], vec.size());
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &chain;
        body->CreateFixture(&fixtureDef);
    }

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

    updateTail();

}
