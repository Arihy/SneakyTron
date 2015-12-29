#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui>
#include <QTimer>

#include "openglwindow.h"
#include "player.h"
#include "border.h"
#include "physic.h"
#include "particles.h"


class GameWindow : public OpenGLWindow
{
    Q_OBJECT
private:
    Physic myWorld;

    GLuint loadShader(GLenum type, const char *source);
    QVector<Player> _player;
    QVector<Border*> _border;
    QVector<QVector4D> _colorList;
    QVector<Particles> _particlesSystem;

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
    QTimer *_physicTimer;

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
