#ifndef LOADER_H
#define LOADER_H
#include <QObject>
#include <QMovie>
#include <QSplashScreen>
class Loader : public QSplashScreen
{

    Q_OBJECT

public:
    Loader(const QPixmap & pixmap);
    Loader(const QString gifname);
    ~Loader();
protected:
    virtual void drawContents(QPainter *painter);
    void setGif(QString fileName);
private slots:
    void slot_update();

private:
    QMovie *m_movie = nullptr;
    int m_framecount;
};

#endif // LOADER_H
