#include "gamewindow.h"
#include "player.h"

#include <QVector3D>
#include <QVector>

#define NB_PLAYER 4

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

    initializeGame();


    _physicTimer = new QTimer();
    connect(_physicTimer, SIGNAL(timeout()), &myWorld, SLOT(tick()));
    _physicTimer->start(30);


    _renderTimer = new QTimer();  
    connect(_renderTimer, SIGNAL(timeout()), this, SLOT(renderNow()));
    _renderTimer->start(30);


    _tailTimer = new QTimer();
    _tailTimer->start(30);
    connect(_tailTimer, SIGNAL(timeout()), this, SLOT(updateTails()));
}

GameWindow::~GameWindow()
{
}

void GameWindow::initialize()
{
    initPlayerShaderPrograme();
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
    _playerColAttr = _playerProgram->attributeLocation("colAttr");
    _matrixUniform = _playerProgram->uniformLocation("matrix");

    QVector<QVector3D> position;
    QVector<QVector4D> colors;
    for(Player player : _player)
    {
        position.push_back(player.position());
        colors.push_back(player.color());
    }

    size_t posSize = sizeof(QVector3D)*position.size(), colSize = sizeof(QVector4D)*colors.size();

    _playerVao.create();
    _playerVao.bind();

    _playerVbo.create();
    _playerVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _playerVbo.bind();

    _playerVbo.allocate(posSize + colSize);

    _playerVao.bind();
    _playerVbo.write(0, position.constData(), posSize);
    _playerVbo.write(posSize, colors.constData(), colSize);

    _playerProgram->setAttributeBuffer(_playerPosAttr, GL_FLOAT, 0, 3, 0);
    _playerProgram->setAttributeBuffer(_playerColAttr, GL_FLOAT, posSize, 3, 0);

    _playerProgram->enableAttributeArray(_playerPosAttr);
    _playerProgram->enableAttributeArray(_playerColAttr);

    _playerVao.release();

    _playerProgram->release();
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
        _player.push_back(Player(_controller[i], QVector3D(i*0.5f, -.8, 0), _colorList[i]));
    }

    QVector<Player *> temp;
    for (int i=0 ;i <_player.size();i++){
        temp<< &_player[i];
    }
    myWorld.setPlayers(temp);
    myWorld.init();






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

void GameWindow::updateGame()
{
    for(Player &player : _player)
    {
        player.computeDirection();
    }
}

void GameWindow::render(){
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    updateGame();

    _playerProgram->bind();

    QMatrix4x4 matrix;
    matrix.perspective(50.0f, 16.0f/9.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);

    _playerProgram->setUniformValue(_matrixUniform, matrix);

    _playerVao.bind();
    _playerVbo.bind();

    QVector<QVector3D> position;
    for(Player player : _player)
    {
        position.push_back(player.position());
    }

    size_t posSize = sizeof(QVector3D)*position.size();
    _playerVbo.write(0, position.constData(), posSize);

    glDrawArrays(GL_POINTS, 0, NB_PLAYER);

    _playerVao.release();
    _playerProgram->release();

    for(Player player : _player)
    {
        _tailsProgram->bind();
        _tailsProgram->setUniformValue(_matrixUniform, matrix);

        _tailsProgram->setUniformValue(_tailsColAttr, player.color());

        _tailsVao.bind();
        _tailsVbo.bind();

        size_t tailSize = player.tail().size()*sizeof(QVector3D);
        _tailsVbo.allocate(tailSize);
        _tailsVbo.write(0, player.tail().constData(), tailSize);
        glDrawArrays(GL_LINE_STRIP, 0, player.tail().size());

        _tailsVao.release();
        _tailsProgram->release();
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    for(int i = 0;  i<_player.size();  i++)
    {
        _player[i].keyPressEvent(event);
    }

    switch(event->key())
    {
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_R:
        initializeGame();
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
