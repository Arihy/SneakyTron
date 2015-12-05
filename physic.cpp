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
}

void Physic::initBorder()
{


    b2BodyDef borderBodyDef[_borders.size()];
    b2PolygonShape borderBox[_borders.size()];
    for (int i=0; i<_borders.size();i++){
        borderBodyDef[i].position.Set(_borders[i]->position().x(), _borders[i]->position().y());
        borderBodyDef[i].type = b2_staticBody;
        _borderBody[i] = _world.CreateBody(&borderBodyDef[i]);
        borderBox[i].SetAsBox(_borders[i]->dimension().x(), _borders[i]->dimension().y());
        qDebug()<<"position : "<<_borders[i]->position()<<" hald-dim : "<<_borders[i]->dimension();
        _borderBody[i]->CreateFixture(&borderBox[i], 1.0f);
        _borderBody[i]->SetUserData(_borders[i]);
    }



//    borderBodyDef[0].position.Set(0.0f, 1.0f);
//    borderBodyDef[0].type = b2_staticBody;
//    _borderBody[0] = _world.CreateBody(&borderBodyDef[1]);
//    borderBox[0].SetAsBox(1.0f, 0.1f);
//    _borderBody[0]->CreateFixture(&borderBox[0], 1.0f);

//    borderBodyDef[1].position.Set(1.0f, 0.0f);
//    borderBodyDef[1].type = b2_staticBody;
//    _borderBody[1] = _world.CreateBody(&borderBodyDef[1]);
//    borderBox[1].SetAsBox(0.1f, 1.0f);
//    _borderBody[1]->CreateFixture(&borderBox[1], 1.0f);

//    borderBodyDef[2].position.Set(0.0f, -1.0f);
//    borderBodyDef[2].type = b2_staticBody;
//    _borderBody[2] = _world.CreateBody(&borderBodyDef[2]);
//    borderBox[2].SetAsBox(1.0f, 0.1f);
//    _borderBody[2]->CreateFixture(&borderBox[2], 1.0f);

//    borderBodyDef[3].position.Set(-1.0f, 0.0f);
//    borderBodyDef[3].type = b2_staticBody;
//    _borderBody[3] = _world.CreateBody(&borderBodyDef[3]);
//    borderBox[3].SetAsBox(0.1f, 1.0f);
//    _borderBody[3]->CreateFixture(&borderBox[3], 1.0f);


}

void Physic::initPlayer()
{

    b2CircleShape playerShape;
    playerShape.m_p.Set(0, 0); //position, relative to body position
    playerShape.m_radius = 0.01; // radius

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape=&playerShape;
    playerFixtureDef.density=0;

    _playersBody.clear();
     for (int i=0 ;i <_players.size();i++){
         b2BodyDef playerBodyDef;
         playerBodyDef.type = b2_dynamicBody;

         playerBodyDef.position.Set( _players[i]->position().x()  ,_players[i]->position().y());

         _playersBody<<_world.CreateBody(&playerBodyDef);
         _playersBody[i]->CreateFixture(&playerFixtureDef);
         _playersBody[i]->SetUserData( _players[i]); // Bind du body avec l'objet player
     }
     qDebug()<<(static_cast<Entity*>(_playersBody[1]->GetUserData())->getEntityType() == PLAYER);

}


void Physic::updateDirection()
{
    for(Player* player : _players)
    {
        player->computeDirection();
    }
}

void Physic::tick(){

    float32 timeStep = 30.0f/1000.0f;


    int32 velocityIterations = 6;
    int32 positionIterations = 2;


    updateDirection();

        for (int i=0 ;i <_players.size();i++){

             _playersBody[i]->SetLinearVelocity(10*b2Vec2(_players[i]->direction().x()*_players[i]->moveSpeed(),_players[i]->direction().y()*_players[i]->moveSpeed()));
         }
    _world.Step(timeStep, velocityIterations, positionIterations);

        for (int i=0 ;i <_players.size();i++){
            b2Vec2 position = _playersBody[i]->GetPosition();
            _players[i]->setPosition(QVector3D(position.x, position.y, 0));
        }

}



