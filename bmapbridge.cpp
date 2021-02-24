#include "bmapbridge.h"

BmapBridge::BmapBridge(QObject *parent) : QObject(parent)
{

}

void BmapBridge::setCoordinate(QString lon, QString lat)
{
    emit setCoordinateSignal(lon, lat);
}

void BmapBridge::createNode(QString name, double lon, double lat)
{
    emit createNodeSignal(name, lon, lat);
}

void BmapBridge::createFiberLink(QString name, int from, int to, int size, double length)
{
    emit createFiberLinkSignal(name, from, to, size, length);
}

