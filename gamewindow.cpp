#include "gamewindow.h"
#include "player.h"

#define NB_PLAYER 2

GameWindow::GameWindow()
{
    for(int i = 0; i < NB_PLAYER; i++)
        _player.push_back(Player(QVector3D(i, 0, 0), QVector4D(i, 0, 0, 1)));
}

void GameWindow::initialize(){

    _playerProgram = new QOpenGLShaderProgram(this);
    _playerProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/Player_vertex_shader");

    _playerProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Player_fragment_shader");
    _playerProgram->link();

    _playerProgram->bind();


    _playerPosAttr=_playerProgram->attributeLocation("posAttr");
    _playerColAttr=_playerProgram->attributeLocation("colAttr");

    _playerVao.create();

    _playerVao.bind();

    QVector<QVector3D> position;
    for(int i = 0; i < NB_PLAYER; i++)
    {
        position<<_player[i].position();
    }
    int posSize=sizeof(position[0]*position.size());

    _playerVboPos.create();

    _playerVboPos.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _playerVboPos.bind();
    _playerVboPos.allocate(posSize);
    _playerVboPos.write(0, position.constData(), posSize);

    _playerProgram->setAttributeBuffer(_playerPosAttr, GL_FLOAT, 0, 3, 0);


    QVector<QVector4D> colors;
    for(int i = 0; i < NB_PLAYER; i++)
    {
        colors<<_player[i].color();
    }
    int colSize=sizeof(colors[0]*colors.size());

    _playerVboCol.create();

    _playerVboCol.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _playerVboCol.bind();
    _playerVboCol.allocate(colSize);
    _playerVboCol.write(0, colors.constData(), colSize);

    _playerProgram->setAttributeBuffer(_playerColAttr, GL_FLOAT, 0, 4, 0);

    _playerProgram->enableAttributeArray(_playerPosAttr);
    _playerProgram->enableAttributeArray(_playerColAttr);
           qDebug()<<"still no crash ..";

    _playerProgram->release();
    _playerVao.release();

}

void GameWindow::render(){
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);



    _playerProgram->bind();
    _playerVao.bind();

    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_POINTS, 0, NB_PLAYER);


    _playerVao.release();
    _playerProgram->release();
}
