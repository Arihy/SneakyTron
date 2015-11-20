#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui>

#include "openglwindow.h"
#include "player.h"


class GameWindow : public OpenGLWindow
{
private:
    GLuint loadShader(GLenum type, const char *source);
    QVector<Player> _player;

    GLuint _playerPosAttr, _playerColAttr;
    GLuint _matrixUniform;
    QOpenGLShaderProgram *_playerProgram;
    QOpenGLVertexArrayObject _playerVao;
    QOpenGLBuffer _playerVbo;

public:
    GameWindow();
    void render();
    void initialize();
};

#endif // GAMEWINDOW_H
