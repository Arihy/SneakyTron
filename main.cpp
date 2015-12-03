#include "openglwindow.h"
#include "gamewindow.h"
#include "physic.h"
#include <QtGui/QGuiApplication>


int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    

    QSurfaceFormat format;
    format.setSamples(16);

    GameWindow window;
    window.setFormat(format);

    window.resize(1024, 751);
    window.show();

    window.setAnimating(false);
    return app.exec();
}

