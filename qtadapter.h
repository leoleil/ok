#ifndef QTADAPTER_H
#define QTADAPTER_H
#include <QString>
#include <string>

class QtAdapter
{
public:
    QtAdapter();
    static QString str2qstr(const std::string str);
    static std::string qstr2str(const QString qstr);
};

#endif // QTADAPTER_H
