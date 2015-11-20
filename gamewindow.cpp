#include "gamewindow.h"
#include "player.h"

#define NB_PLAYER 2

GameWindow::GameWindow() : _playerProgram(0)
{
    for(int i = 0; i < NB_PLAYER; i++)
        _player.push_back(Player(QVector3D(i*0.5f, 0, 0), QVector3D(i, 1, 0)));
}

void GameWindow::initialize(){

    _playerProgram = new QOpenGLShaderProgram(this);

    _playerProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/player.vert");
    _playerProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/player.frag");

    _playerProgram->link();

    _playerPosAttr = _playerProgram->attributeLocation("posAttr");
    _playerColAttr = _playerProgram->attributeLocation("colAttr");
    _matrixUniform = _playerProgram->uniformLocation("matrix");

    QVector<QVector3D> position, colors;
    for(int i = 0; i < NB_PLAYER; i++)
    {
        position.push_back(_player[i].position());
        colors.push_back(_player[i].color());
    }

    size_t posSize = sizeof(QVector3D)*position.size(), colSize = sizeof(QVector3D)*colors.size();

    _playerVao.create();
    _playerVao.bind();

    _playerVbo.create();
    _playerVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _playerVbo.bind();

    _playerVbo.allocate(posSize + colSize);

    _playerVao.bind();
    _playerVbo.write(0, position.constData(), posSize);
    _playerVbo.write(posSize, colors.constData(), posSize);

    _playerProgram->setAttributeBuffer(_playerPosAttr, GL_FLOAT, 0, 3, 0);
    _playerProgram->setAttributeBuffer(_playerColAttr, GL_FLOAT, posSize, 3, 0);

    _playerProgram->enableAttributeArray(_playerPosAttr);
    _playerProgram->enableAttributeArray(_playerColAttr);

    _playerVao.release();

    _playerProgram->release();
}

GLuint GameWindow::loadShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    return shader;
}

void GameWindow::render(){
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    _playerProgram->bind();

    QMatrix4x4 matrix;
    matrix.perspective(50.0f, 16.0f/9.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);

    _playerProgram->setUniformValue(_matrixUniform, matrix);

    _playerVao.bind();

    glDrawArrays(GL_POINTS, 0, NB_PLAYER);

    _playerVao.release();
    _playerProgram->release();
}
