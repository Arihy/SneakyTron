#include "openglwindow.h"
#include "gamewindow.h"
#include <QtGui/QGuiApplication>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(1);
    format.setVersion(3,3);

    GameWindow window;
    window.setFormat(format);

    window.resize(1024, 800);
    window.show();

    window.setAnimating(false);
    return app.exec();
}

