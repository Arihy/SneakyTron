#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "openglwindow.h"
#include "player.h"


class GameWindow : public OpenGLWindow
{
private:
    QVector<Player> _player;
public:
    GameWindow();
};

#endif // GAMEWINDOW_H
