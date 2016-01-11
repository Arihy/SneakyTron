#include "gamewindow.h"
#include "player.h"

#include <QVector3D>
#include <QVector>

static const int NB_PLAYER = 4;
static const int HALF_DIM_BOARD = 1;


GameWindow::GameWindow() : _playerProgram(0), _tailsProgram(0)
{
    QVector<Qt::Key> controller;
    controller.push_back(Qt::Key_Q);
    controller.push_back(Qt::Key_D);
    _controller.push_back(controller);
    controller.clear();
    controller.push_back(Qt::Key_Left);
    controller.push_back(Qt::Key_Right);
    _controller.push_back(controller);
    controller.clear();
    controller.push_back(Qt::Key_I);
    controller.push_back(Qt::Key_P);
    _controller.push_back(controller);
    controller.clear();
    controller.push_back(Qt::Key_F);
    controller.push_back(Qt::Key_H);
    _controller.push_back(controller);

    _colorList.push_back(QVector4D(1.0, 0.2, 0.2, 1.0));
    _colorList.push_back(QVector4D(0.2, 1.0, 0.2, 1.0));
    _colorList.push_back(QVector4D(0.2, 0.2, 1.0, 1.0));
    _colorList.push_back(QVector4D(1.0, 1.0, 0.2, 1.0));

    _particlesSystem.push_back(new Particles(QVector4D(1.0, 0.2, 0.2, 1.0)));
    _particlesSystem.push_back(new Particles(QVector4D(0.2, 1.0, 0.2, 1.0)));
    _particlesSystem.push_back(new Particles(QVector4D(0.2, 0.2, 1.0, 1.0)));
    _particlesSystem.push_back(new Particles(QVector4D(1.0, 1.0, 0.2, 1.0)));



    _physicTimer = new QTimer();
    connect(_physicTimer, SIGNAL(timeout()), &myWorld, SLOT(tick()));

    _renderTimer = new QTimer();
    connect(_renderTimer, SIGNAL(timeout()), this, SLOT(renderNow()));

    _tailTimer = new QTimer();
    connect(_tailTimer, SIGNAL(timeout()), this, SLOT(updateTails()));

    for(Particles *p : _particlesSystem)
    {
        connect(_renderTimer, SIGNAL(timeout()), p, SLOT(update()));
    }

    connect(myWorld.getMyColliderInstance(),SIGNAL(playerExplodes(Player*)),this,SLOT(playerExplodes(Player*)));

    initializeGame();
}

GameWindow::~GameWindow()
{
}

void GameWindow::initialize()
{
    initPlayerShaderPrograme();
    initParticlesShaderPrograme();
    initTailsShaderPrograme();
}

void GameWindow::initPlayerShaderPrograme()
{
    _playerProgram = new QOpenGLShaderProgram(this);

    _playerProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/player.vert");
    _playerProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/player.frag");

    _playerProgram->link();

    _playerProgram->bind();

    _playerPosAttr = _playerProgram->attributeLocation("posAttr");
    _playerCenterUni = _playerProgram->uniformLocation("playerCenter");
    _playerColUni = _playerProgram->uniformLocation("colUni");
    _matrixUniform = _playerProgram->uniformLocation("matrix");

    _playerVao.create();
    _playerVao.bind();

    _playerVbo.create();
    _playerVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _playerVbo.bind();

    _playerVao.bind();

    _playerProgram->setAttributeBuffer(_playerPosAttr, GL_FLOAT, 0, 3, 0);

    _playerProgram->enableAttributeArray(_playerPosAttr);

    _playerVao.release();

    _playerProgram->release();
}

void GameWindow::initParticlesShaderPrograme()
{
    _particlesProgram = new QOpenGLShaderProgram(this);

    _particlesProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/tail.vert");
    _particlesProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/tail.frag");

    _particlesProgram->link();

    _particlesProgram->bind();

    _particlesPosAttr = _particlesProgram->attributeLocation("posAttr");
    _particlesColAttr = _particlesProgram->uniformLocation("colAttr");
    _matrixUniform = _particlesProgram->uniformLocation("matrix");

    _particlesVao.create();
    _particlesVao.bind();

    _particlesVbo.create();
    _particlesVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _particlesVbo.bind();

    _particlesProgram->setAttributeBuffer(_particlesPosAttr, GL_FLOAT, 0, 3, 0);

    _particlesProgram->enableAttributeArray(_particlesPosAttr);
    _particlesProgram->enableAttributeArray(_particlesColAttr);

    _particlesVao.release();

    _particlesProgram->release();
}

void GameWindow::initTailsShaderPrograme()
{
    _tailsProgram = new QOpenGLShaderProgram(this);

    _tailsProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/tail.vert");
    _tailsProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/tail.frag");

    _tailsProgram->link();

    _tailsPosAttr = _tailsProgram->attributeLocation("posAttr");
    _tailsColAttr = _tailsProgram->uniformLocation("colAttr");
    _matrixUniform = _tailsProgram->uniformLocation("matrix");

    _tailsVao.create();
    _tailsVao.bind();

    _tailsVbo.create();
    _tailsVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _tailsVbo.bind();

    _tailsProgram->setAttributeBuffer(_tailsPosAttr, GL_FLOAT, 0, 3, 0);
    _tailsProgram->enableAttributeArray(_tailsPosAttr);

    _tailsVao.release();
    _tailsProgram->release();
}

void GameWindow::initializeGame()
{
    _player.clear();
    for(int i = 0; i < NB_PLAYER; i++)
    {
        _player.push_back(Player(i + 1,_controller[i], QVector3D((-HALF_DIM_BOARD+0.2)+((2*HALF_DIM_BOARD-0.4)/(NB_PLAYER+1))*(i), -HALF_DIM_BOARD+0.3, 0), _colorList[i]));
    }

    QVector<Player *> temp;
    for (int i=0 ;i <_player.size();i++){
        temp<< &_player[i];
    }

    QVector< QVector2D> vec;
    vec<<QVector2D(-1,-1)<<QVector2D(-1,1)<<QVector2D(1,1)<<QVector2D(1,-1);
    _border = new Border(vec);

    myWorld.setBorder(_border);
    myWorld.setPlayers(temp);
    myWorld.init();

    _physicTimer->start(30);

    _renderTimer->start(30);

    _tailTimer->start(30);

}

void GameWindow::updateTails()
{
    for(Player &player : _player)
    {
        player.updateTail();
    }
}

GLuint GameWindow::loadShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    return shader;
}

Border *GameWindow::border() const
{
    return _border;
}

void GameWindow::setBorder(Border *border)
{
    _border = border;
}


void GameWindow::render(){
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    QMatrix4x4 matrix;
    matrix.perspective(50.0f, 16.0f/9.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);

    for(Player &player : _player)
    {
        _playerProgram->bind();
        _playerProgram->setUniformValue(_matrixUniform, matrix);
        _playerProgram->setUniformValue(_playerColUni, player.color());
        _playerProgram->setUniformValue(_playerCenterUni, QVector3D(10,10,10));

        _playerVao.bind();
        _playerVbo.bind();

        QVector<QVector3D> playerShape;
        QVector3D cornerDistanceToCenter = QVector3D(0.01f, 0.01f, 0.0f);
        playerShape << cornerDistanceToCenter +player.position();
        cornerDistanceToCenter = QVector3D(0.01f, -0.01f, 0.0f);
        playerShape << cornerDistanceToCenter+player.position();
        cornerDistanceToCenter = QVector3D(-0.01f, -0.01f, 0.0f);
        playerShape << cornerDistanceToCenter+player.position();
        cornerDistanceToCenter = QVector3D(-0.01f, 0.01f, 0.0f);
        playerShape << cornerDistanceToCenter+player.position();

        size_t posSize = playerShape.size() * sizeof(QVector3D);
        _playerVbo.allocate(posSize);
        _playerVbo.write(0, playerShape.constData(), posSize);

        glDrawArrays(GL_POLYGON, 0, playerShape.size());

        _playerVao.release();
        _playerProgram->release();
    }

    for(Player player : _player)
    {
        _tailsProgram->bind();
        _tailsProgram->setUniformValue(_matrixUniform, matrix);

        _tailsProgram->setUniformValue(_tailsColAttr, player.color());

        _tailsVao.bind();
        _tailsVbo.bind();

        size_t tailSize = player.tail()->size()*sizeof(QVector3D);
        _tailsVbo.allocate(tailSize);
        _tailsVbo.write(0, player.tail()->getChain().constData(), tailSize);

        glDrawArrays(GL_LINE_STRIP, 0, player.tail()->size());

        _tailsVao.release();
        _tailsProgram->release();


    }

    for(Particles *p : _particlesSystem)
    {
        if(p->getParticlesPosition().size() <= 0)
            continue;
        _particlesProgram->bind();
        _particlesProgram->setUniformValue(_matrixUniform, matrix);

        _particlesProgram->setUniformValue(_particlesColAttr, p->getColor());

        _particlesVao.bind();
        _particlesVbo.bind();

        size_t particlesSize = p->getParticlesPosition().size()*sizeof(QVector3D);
        _particlesVbo.allocate(particlesSize);
        _particlesVbo.write(0, p->getParticlesPosition().constData(), particlesSize);

        glDrawArrays(GL_POINTS, 0, p->getParticlesPosition().size());

        _particlesVao.release();
        _particlesProgram->release();
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    for(Player &player : _player)
    {
        player.keyPressEvent(event);
    }

    switch(event->key())
    {
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_R:
        resetWorld();
        break;
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *event)
{
    for(Player &player : _player)
    {
        player.keyReleaseEvent(event);
    }
}

// SLOT

void GameWindow::playerExplodes(Player *player)
{
    if(_particlesSystem[player->getId()-1]->animationDone())
        _particlesSystem[player->getId()-1]->initParticles(player->position());
    qDebug() << "player " << player->getId() << " crashed !";
}

void GameWindow::updateGame()
{
    for(Player &player : _player)
    {
        player.computeDirection();
    }
}

void GameWindow::resetWorld()
{
    myWorld.resetWorldContent();
    QTimer* endTimer;
    endTimer->singleShot(35,&myWorld, SLOT(tick()));
    endTimer->singleShot(35,this, SLOT(initializeGame()));
}

