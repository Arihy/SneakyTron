#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "openglwindow.h"
#include "player.h"


class GameWindow : public OpenGLWindow
{
private:
    QVector<Player> _player;

    GLuint _player_posAttr, _player_colAttr;
    QOpenGLShaderProgram *_player_program;
    QOpenGLVertexArrayObject _player_vao;
    QOpenGLBuffer _player_vbo_pos,_player_vbo_col ;

public:
    GameWindow();
    void render();
    void initialize();

};

#endif // GAMEWINDOW_H
