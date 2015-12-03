#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui>
#include <QTimer>

#include "openglwindow.h"
#include "player.h"


class GameWindow : public OpenGLWindow
{
    Q_OBJECT
private:
    GLuint loadShader(GLenum type, const char *source);
    QVector<Player> _player;
    QVector<QVector4D> _colorList;

    GLuint _playerPosAttr, _playerColAttr;
    GLuint _tailsPosAttr, _tailsColAttr;
    GLuint _matrixUniform;

    QOpenGLShaderProgram *_playerProgram;
    QOpenGLVertexArrayObject _playerVao;
    QOpenGLBuffer _playerVbo;

    QOpenGLShaderProgram *_tailsProgram;
    QOpenGLVertexArrayObject _tailsVao;
    QOpenGLBuffer _tailsVbo;

    QTimer *_renderTimer;
    QTimer *_tailTimer;

    QVector< QVector<Qt::Key> > _controller;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void initPlayerShaderPrograme();
    void initTailsShaderPrograme();

public:
    GameWindow();
    ~GameWindow();
    void render();
    void initialize();
    void updateGame();
    void initializeGame();

public slots:
    void updateTails();
};

#endif // GAMEWINDOW_H
