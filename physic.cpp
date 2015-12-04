#include "physic.h"

QVector<Player *> Physic::players() const
{
    return _players;
}

void Physic::setPlayers(const QVector<Player *> &players)
{
    this->_players = players;
}

Physic::Physic():_world(b2Vec2(0.0f, 0.0f))
{

}

Physic::Physic(QVector<Player *> listPlayer):_world(b2Vec2(0.0f, 0.0f))
{
    _players=listPlayer;
}

void Physic::init(){
    initGround();
    initPlayer();
}

void Physic::initGround()
{
    b2BodyDef groundBodyDef[4];
    b2PolygonShape groundBox[4];

    groundBodyDef[0].position.Set(0.0f, 1.0f);
    groundBodyDef[0].type = b2_staticBody;
    _groundBody[0] = _world.CreateBody(&groundBodyDef[0]);
    groundBox[0].SetAsBox(1.0f, 0.1f);
    _groundBody[0]->CreateFixture(&groundBox[0], 1.0f);

    groundBodyDef[1].position.Set(1.0f, 0.0f);
    groundBodyDef[1].type = b2_staticBody;
    _groundBody[1] = _world.CreateBody(&groundBodyDef[1]);
    groundBox[1].SetAsBox(0.1f, 1.0f);
    _groundBody[1]->CreateFixture(&groundBox[1], 1.0f);

    groundBodyDef[2].position.Set(0.0f, -1.0f);
    groundBodyDef[2].type = b2_staticBody;
    _groundBody[2] = _world.CreateBody(&groundBodyDef[2]);
    groundBox[2].SetAsBox(1.0f, 0.1f);
    _groundBody[2]->CreateFixture(&groundBox[2], 1.0f);

    groundBodyDef[3].position.Set(-1.0f, 0.0f);
    groundBodyDef[3].type = b2_staticBody;
    _groundBody[3] = _world.CreateBody(&groundBodyDef[3]);
    groundBox[3].SetAsBox(0.1f, 1.0f);
    _groundBody[3]->CreateFixture(&groundBox[3], 1.0f);


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



