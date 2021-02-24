#ifndef BMAPBRIDGE_H
#define BMAPBRIDGE_H
#include <QObject>
class BmapBridge : public QObject
{
    Q_OBJECT
public:
    explicit BmapBridge(QObject *parent = nullptr);

signals:
    void setCoordinateSignal(QString lon,QString lat);//设置经纬度信号
    void createNodeSignal(QString name, double lon, double lat);// 创建节点信号
    void createFiberLinkSignal(QString name, int from, int to, int size, double length);// 创建链路信号
public slots:
    void setCoordinate(QString lon,QString lat);//设置经纬度
    void createNode(QString name, double lon, double lat);// 创建节点
    void createFiberLink(QString name, int from, int to, int size, double length);// 创建链路
public:

};

#endif // BMAPBRIDGE_H
