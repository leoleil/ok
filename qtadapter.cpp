#include "qtadapter.h"

QtAdapter::QtAdapter()
{

}

QString QtAdapter::str2qstr(const std::string str)
{
    return QString::fromLocal8Bit(str.data());
}

std::string QtAdapter::qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return std::string(cdata);
}
