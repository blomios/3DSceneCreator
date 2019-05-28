#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "mainwindow.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute( Qt::AA_UseDesktopOpenGL );

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("3DSceneCreator");
    app.setApplicationVersion("1.0");
#ifndef QT_NO_OPENGL
    MainWindow window;
    window.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
