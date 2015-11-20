#include "gamewindow.h"
#include "player.h"

#define NB_PLAYER 2

GameWindow::GameWindow()
{
    for(int i = 0; i < NB_PLAYER; i++)
        _player.push_back(Player(QVector2D(i, 0), QVector4D(i, 0, 0, 1)));
}

void GameWindow::initialize(){

    _player_program = new QOpenGLShaderProgram(this);
    _player_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/Player_vertex_shader");

    _player_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/Player_fragment_shader");
    _player_program->link();

    _player_program->bind();


    _player_posAttr=_player_program->attributeLocation("posAttr");
    _player_colAttr=_player_program->attributeLocation("colAttr");

    _player_vao.create();

    _player_vao.bind();

    QVector<QVector3D> position;
    for(int i = 0; i < NB_PLAYER; i++)
    {
        position<<_player[i].position();
    }
    int posSize=sizeof(position[0]*position.size());

    _player_vbo_pos.create();

    _player_vbo_pos.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _player_vbo_pos.bind();
    _player_vbo_pos.allocate(posSize);
    _player_vbo_pos.write(0, position.constData(), posSize);

    _player_program->setAttributeBuffer(_player_posAttr, GL_FLOAT, 0, 3, 0);


    QVector<QVector4D> colors;
    for(int i = 0; i < NB_PLAYER; i++)
    {
        colors<<_player[i].color();
    }
    int colSize=sizeof(colors[0]*colors.size());

    _player_vbo_col.create();

    _player_vbo_col.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _player_vbo_col.bind();
    _player_vbo_col.allocate(colSize);
    _player_vbo_col.write(0, colors.constData(), colSize);

    _player_program->setAttributeBuffer(_player_colAttr, GL_FLOAT, 0, 4, 0);

    _player_program->enableAttributeArray(_player_posAttr);
    _player_program->enableAttributeArray(_player_colAttr);
           qDebug()<<"still no crash ..";

    _player_program->release();
    _player_vao.release();

}

void GameWindow::render(){
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);



    _player_program->bind();
    _player_vao.bind();

    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_POINTS, 0, NB_PLAYER);


    _player_vao.release();
    _player_program->release();
}
