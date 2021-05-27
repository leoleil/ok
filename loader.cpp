#include "loader.h"
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include <QDebug>
Loader::Loader(const QPixmap &pixmap):QSplashScreen(pixmap)
{

}
Loader::Loader(const QString gifname)
{
    setGif(gifname);
    QPixmap pixmap(gifname);
    this->setPixmap(pixmap);
}
Loader::~Loader()
{
    if(nullptr != nullptr){
        delete m_movie;
    }
}
void Loader::setGif(QString fileName)
{
    m_movie = new QMovie(fileName);
    m_framecount = m_movie->frameCount();
    connect(m_movie,&QMovie::frameChanged,this,[=](int temp){
        if(temp == (m_framecount-1))
        {
            m_movie->stop();
        }
    });
    m_movie->start();
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_update()));
    timer->start(40);
}
void Loader::drawContents(QPainter *painter)
{
    painter->setFont(QFont("黑体", 10));
    painter->setPen(QColor(213, 218, 220));
    painter->drawText(QPointF(5, 15), "");
    QSplashScreen::drawContents(painter);
}

void Loader::slot_update()
{
    this->setPixmap(m_movie->currentPixmap());
    repaint();
}
