#ifndef DIALOGLINKRES_H
#define DIALOGLINKRES_H

#include <QDialog>
#include <FiberLink.h>
namespace Ui {
class DialogLinkRes;
}

class DialogLinkRes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLinkRes(QWidget *parent = 0);
    ~DialogLinkRes();
    // 加载链路
    void load(FiberLink& link);
private:
    Ui::DialogLinkRes *ui;
    FiberLink* fiberLink;
    void reload();// 刷新
    void reloadWavelengthItem(int index);// 刷新波道信息
    // 更改带宽
    // 更改波道数量
    // 更改模式数量
    // 更改波道波长
};

#endif // DIALOGLINKRES_H
