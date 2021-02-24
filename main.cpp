#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //AA_ShareOpenGLContexts + AA_UseDesktopOpenGL + AA_UseOpenGLES
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    //QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QApplication a(argc, argv);

    MainWindow w;
    //w.showMaximized();
    //w.showFullScreen();
    w.showNormal();
    return a.exec();
}
