#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QWebChannel>
#include "Weaver.h"
#include "Simulator.h"
#include "dialogaddnode.h"
#include "dialogaddfiberlink.h"
#include "dialoglinkres.h"
#include "bmapbridge.h"
#include "dialogplaysimulator.h"
#include "dialogresult.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    // 添加节点
    void createNode(QString name, double x, double y);
    // 添加链路
    void createFiberLink(QString name, int from, int to, int size, double length);
private slots:
    void on_actionNodes_view_triggered();
    void on_actionLinks_view_triggered();
    void on_actionOpenProject_triggered();
    void on_actionSaveProject_triggered();
    void on_actionAdd_node_triggered();
    void on_actionAdd_link_triggered();
    void on_actionexit_triggered();
    void on_actionmap_triggered();
    void on_actionConfig_triggered();
    void on_actionPlay_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scence = nullptr;
    Weaver weaver;
    Simulator simulator;// 仿真模块
    QWebChannel* webChannel;// web 地图显示
    BmapBridge* bmapBridge;
    DialogAddNode* dialogAddNode = nullptr;// 添加节点对话框
    DialogAddFiberLink* dialogAddFiberLink = nullptr;// 添加链路对话框
    DialogLinkRes* dialogLinkRes = nullptr;// 链路资源对话框
    DialogPlaySimulator* dialogPlaySimulator = nullptr;// 仿真配置模块
    DialogResult* dialogReault = nullptr;// 开始仿真模块
private:
    // 节点树显示刷新
    void nodesTreeShow();
    // 链路数显示刷新
    void linksTreeShow();
    // 更新节点到web
    void toJsNodeShow();
    // 更新链路到web
    void toJsLinkShow();
    // 更新虚拟节点到web
    void toJsVNodeShow();
    // 更新虚拟链路到web
    void toJsVLinkShow();
};

#endif // MAINWINDOW_H
