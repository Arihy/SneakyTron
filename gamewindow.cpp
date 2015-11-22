#include "gamewindow.h"
#include "player.h"

#include <QVector3D>
#include <QVector>

#define NB_PLAYER 2

GameWindow::GameWindow() : _playerProgram(0), _tailsProgram(0)
{
    _colorList = new QVector4D[4];
    _colorList[0] = QVector4D(1.0, 0.2, 0.2, 1.0);
    _colorList[1] = QVector4D(0.2, 1.0, 0.2, 1.0);
    _colorList[2] = QVector4D(0.2, 0.2, 1.0, 1.0);
    _colorList[3] = QVector4D(1.0, 1.0, 0.2, 1.0);

    initializeGame();

    _renderTimer = new QTimer();
    _renderTimer->start(30);
    connect(_renderTimer, SIGNAL(timeout()), this, SLOT(renderNow()));

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

    _playerPosAttr = _playerProgram->attributeLocation("posAttr");
    _playerColAttr = _playerProgram->attributeLocation("colAttr");
    _matrixUniform = _playerProgram->uniformLocation("matrix");

    QVector<QVector3D> position;
    QVector<QVector4D> colors;
    for(int i = 0; i < NB_PLAYER; i++)
    {
        position.push_back(_player[i].position());
        colors.push_back(_player[i].color());
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
        _player.push_back(Player(QVector3D(i*0.5f, -.8, 0), _colorList[i]));
    }
}

void GameWindow::updateTails()
{
    for(int i = 0; i < NB_PLAYER; i++)
    {
        _player[i].updateTail();
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
    for(int i = 0; i < NB_PLAYER; i++)
    {
        _player[i].move();
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
    _playerProgram->setAttributeValue(_playerPosAttr, NB_PLAYER);
    _playerProgram->setAttributeValue(_playerColAttr, NB_PLAYER);

    _playerVao.bind();
    _playerVbo.bind();
    QVector<QVector3D> position;
    QVector<QVector4D> colors;
    for(int i = 0; i < NB_PLAYER; i++)
    {
        position.push_back(_player[i].position());
        colors.push_back(_player[i].color());
    }

    size_t posSize = sizeof(QVector3D)*position.size(), colSize = sizeof(QVector4D)*colors.size();
    _playerVbo.write(0, position.constData(), posSize);
    _playerVbo.write(posSize, colors.constData(), colSize);

    glDrawArrays(GL_POINTS, 0, NB_PLAYER);

    _playerVao.release();
    _playerProgram->release();

    for(int i = 0; i < NB_PLAYER; i++)
    {
        _tailsProgram->bind();
        _tailsProgram->setUniformValue(_matrixUniform, matrix);

        _tailsProgram->setUniformValue(_tailsColAttr, _player[i].color());

        _tailsVao.bind();

        _tailsVbo.bind();
        size_t tailSize = _player[i].tail().size()*sizeof(QVector3D);
        _tailsVbo.allocate(tailSize);
        _tailsVbo.write(0, _player[i].tail().constData(), tailSize);
        glDrawArrays(GL_LINE_STRIP, 0, _player[i].tail().size());


        _tailsVao.release();

        _tailsProgram->release();
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
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