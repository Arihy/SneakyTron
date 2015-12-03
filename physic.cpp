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


     // le sol
     b2BodyDef groundBodyDef;
     groundBodyDef.position.Set(0.0f, 1.0f);
     groundBodyDef.type = b2_staticBody;

     _groundBody = _world.CreateBody(&groundBodyDef);

//     b2Vec2 vs[4];
//     vs[0].Set(-1.0f, -1.0f);
//     vs[1].Set(-1.0f, 1.0f);
//     vs[2].Set(1.0f, 1.0f);
//     vs[3].Set(-1.0f, 1.0f);

//     b2ChainShape limit;
//     limit.CreateLoop(vs, 4);

//     _groundBody->CreateFixture(&limit, 1.0f);
     b2PolygonShape groundBox;
     groundBox.SetAsBox(1.0f, 0.1f);

    // Création des body des joueurs


    b2CircleShape playerShape;
    playerShape.m_p.Set(0, 0); //position, relative to body position
    playerShape.m_radius = 0.05; // radius

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape=&playerShape;
    playerFixtureDef.density=0;

    _playersBody.clear();
     for (int i=0 ;i <_players.size();i++){
         b2BodyDef playerBodyDef;
         playerBodyDef.type = b2_dynamicBody;
         qDebug()<<"joueur"<<i<<":"<<_players[i]->position().x() <<","<<_players[i]->position().y();

         playerBodyDef.position.Set( _players[i]->position().x()  ,_players[i]->position().y());
         //playerBodyDef.position.Set( i*2 ,5);

         _playersBody<<_world.CreateBody(&playerBodyDef);
         _playersBody[i]->CreateFixture(&playerFixtureDef);
         _playersBody[i]->SetUserData( _players[i]); // Bind du body avec l'objet player
     }

     // Gestion des contacts


}

void Physic::gameLoop(){
    float32 timeStep = 1.0f / 60.0f;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

//    _playersBody[0]->ApplyLinearImpulse(b2Vec2(0,3) , _playersBody[0]->GetWorldCenter(), true); // Une impulsion
    _playersBody[1]->ApplyForce(b2Vec2(0,3) , _playersBody[1]->GetWorldCenter(), true); // Une force constante
//    _playersBody[1]->SetGravityScale(0.0); // Set l'intensité de la gravité sur un body

    _world.SetGravity(b2Vec2(0.0f,-3.0f));

//    for (int32 i = 0; i < 180; ++i)
    while(true)
    {
        for (int i=0 ;i <_players.size();i++){
             _playersBody[i]->ApplyForce(b2Vec2(_players[i]->direction().x()*_players[i]->moveSpeed(),_players[i]->direction().y()*_players[i]->moveSpeed()) , _playersBody[i]->GetWorldCenter(), true);
         }
    _world.Step(timeStep, velocityIterations, positionIterations);

        for (int i=0 ;i <_players.size();i++){
            b2Vec2 position = _playersBody[i]->GetPosition();
            _players[i]->setPosition(QVector3D(position.x, position.y, 0));
        }
    }

//    qDebug()<<"iteration : " <<i << " joueur 0 mass :"<<_playersBody[0]->GetMass();
//    b2Vec2 position = _playersBody[0]->GetPosition();
//    qDebug()<<position.x<<","<< position.y;
//    qDebug()<<"joueur 1 mass :"<<_playersBody[1]->GetMass();
//    position = _playersBody[1]->GetPosition();
//    qDebug()<<position.x<<","<< position.y;
}

void Physic::tick(){
    //float32 timeStep = 1.0f / 60.0f;
    float32 timeStep = 30.0f/1000.0f;


    int32 velocityIterations = 6;
    int32 positionIterations = 2;

   // _playersBody[1]->ApplyForce(b2Vec2(-1,3) , _playersBody[1]->GetWorldCenter(), true); // Une force constante
    //_playersBody[1]->SetGravityScale(0.0); // Set l'intensité de la gravité sur un body


        for (int i=0 ;i <_players.size();i++){

             _playersBody[i]->SetLinearVelocity(10*b2Vec2(_players[i]->direction().x()*_players[i]->moveSpeed(),_players[i]->direction().y()*_players[i]->moveSpeed()));
         }
    _world.Step(timeStep, velocityIterations, positionIterations);

        for (int i=0 ;i <_players.size();i++){
            b2Vec2 position = _playersBody[i]->GetPosition();
            _players[i]->setPosition(QVector3D(position.x, position.y, 0));
        }


//        qDebug()<<"player velocity PHYSIC"<<_playersBody[0]->GetLinearVelocity().x<<","<<_playersBody[0]->GetLinearVelocity().y;
//        qDebug()<<"player direction"<<_players[0]->direction();
//        qDebug()<<"player direction Physic :"<<_players[0]->direction().x()<<","<<_players[0]->direction().y();

//        qDebug()<<_playersBody[0]->GetPosition().x<<","<<_playersBody[0]->GetPosition().y;
//        qDebug()<<"player position"<<_players[0]->position();

}

