#include "gamewindow.h"
#include "player.h"

#define NB_PLAYER 2

GameWindow::GameWindow()
{
    for(int i = 0; i < NB_PLAYER; i++)
        _player.push_back(Player(QVector2D(i, 0), QVector4D(i, 0, 0, 1)));
}

