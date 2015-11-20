#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui>

#include "openglwindow.h"
#include "player.h"


class GameWindow : public OpenGLWindow
{
private:
    QVector<Player> _player;

    GLuint _playerPosAttr, _playerColAttr;
    QOpenGLShaderProgram *_playerProgram;
    QOpenGLVertexArrayObject _playerVao;
    QOpenGLBuffer _playerVboPos, _playerVboCol ;

public:
    GameWindow();
    void render();
    void initialize();

};

#endif // GAMEWINDOW_H
