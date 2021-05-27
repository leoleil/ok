#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include "loader.h"
int main(int argc, char *argv[])
{
    //AA_ShareOpenGLContexts + AA_UseDesktopOpenGL + AA_UseOpenGLES
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);
    //加载并显示启动画面
    Loader *loader = new Loader(":/img/insta.gif");
    loader->show();
    Qt::Alignment b_l = Qt::AlignLeft | Qt::AlignBottom;
    loader->showMessage(QObject::tr("Loading"), b_l, Qt::white);
    QDateTime n = QDateTime::currentDateTime();
    QDateTime now;
    do{
        now = QDateTime::currentDateTime();
        a.processEvents();
        if(n.secsTo(now) % 3 == 0){
            loader->showMessage(QObject::tr("Loading."), b_l, Qt::white);
        }else if(n.secsTo(now) % 3== 1){
            loader->showMessage(QObject::tr("Loading.."), b_l, Qt::white);
        }else{
            loader->showMessage(QObject::tr("Loading..."), b_l, Qt::white);
        }

    }while (n.secsTo(now)<=11);
    a.processEvents();
    MainWindow w;

    loader->showMessage(QObject::tr("Welcome"), b_l, Qt::white);
    w.showFullScreen();
    //w.showMaximized();
    loader->finish(&w);
    delete loader;
    return a.exec();
}
