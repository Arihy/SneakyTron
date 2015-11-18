
#include "openglwindow.h"
#include "gamewindow.h"
#include <QtGui/QGuiApplication>
#include <QCoreApplication>


#include <QtCore/qmath.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <time.h>

#include <iostream>

#include <QtCore>
#include <QtGui>

#include <omp.h>
int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    
    
    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(1);
   format.setVersion(3,3);

    GameWindow window;
    window.setFormat(format);

    window.resize(640, 480);
    window.show();

    window.setAnimating(false);
    return a.exec();
}

