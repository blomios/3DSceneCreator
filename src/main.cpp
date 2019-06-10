#ifndef QT_NO_OPENGL

#include "MainWindow.h"

#endif

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication::setApplicationName("Chew Toy Creator");
    QApplication::setApplicationVersion("1.0");
    QApplication::setWindowIcon(QIcon(":/icon.png"));

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
#ifndef QT_NO_OPENGL
    MainWindow window;
    window.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return QApplication::exec();
}
