#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QFileDialog>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QTreeWidget>
#include <QIcon>
#include <QTreeWidgetItem>
#include <QPixmap>
#include <fstream>
#include <QWebChannel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtadapter.h"
#define M_PI        3.14159265358979323846
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 节点添加对话框
    dialogAddNode = new DialogAddNode(this);
    dialogAddNode->close();
    // 链路添加对话框
    dialogAddFiberLink = new DialogAddFiberLink(this);
    dialogAddNode->close();
    // 链路资源对话框
    dialogLinkRes = new DialogLinkRes(this);
    dialogLinkRes->close();
    // 仿真配置对话框
    dialogPlaySimulator = new DialogPlaySimulator(this);
    dialogPlaySimulator->close();
    // 开始仿真对话框
    dialogReault = new DialogResult();
    dialogReault->close();
    // 节点添加事件
    connect(dialogAddNode, &DialogAddNode::createNode, this, &MainWindow::createNode);
    // 链路添加事件
    connect(dialogAddFiberLink, &DialogAddFiberLink::createFiberLink, this, &MainWindow::createFiberLink);
    // web可视化初始化
    webChannel = new QWebChannel(ui->webWidget->page());
    bmapBridge = new BmapBridge(this);
    webChannel->registerObject(QStringLiteral("bmapBridge"), bmapBridge);
    ui->webWidget->page()->setWebChannel(webChannel);
    // 连接 web
    connect(bmapBridge, &BmapBridge::setCoordinateSignal, this,[=](QString x, QString y){
        ui->statusBar->showMessage("x:" + x + " y:" + y, 10000);
    });
    connect(bmapBridge, &BmapBridge::createNodeSignal, this, &MainWindow::createNode);
    connect(bmapBridge, &BmapBridge::createFiberLinkSignal, this, &MainWindow::createFiberLink);
    ui->webWidget->load(QUrl("qrc:/web/map.html"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNodes_view_triggered()
{
    ui->dockWidgetNode->show();
}

void MainWindow::on_actionLinks_view_triggered()
{
    ui->dockWidgetLink->show();
}

void MainWindow::on_actionOpenProject_triggered()
{
    QString s = QFileDialog::getOpenFileName(this, QString(), "*.weaver");
    qDebug() << s.toUtf8().data();
    ifstream ifs(s.toUtf8().data());
    weaver = Weaver();// 清理原来的
    weaver.deserialize(ifs);
    ifs.close(); // 打开文件
    // 节点树显示刷新
    nodesTreeShow();
    // 链路数显示刷新
    linksTreeShow();
    // 更新节点到web
    toJsNodeShow();
    // 更新链路到web
    toJsLinkShow();
    weaver.virtualMap();

}

void MainWindow::on_actionSaveProject_triggered()
{
    QString s = QFileDialog::getSaveFileName(this,QString(),QString(), "*.weaver");
    qDebug() << s.toUtf8().data();
    ofstream ofs(s.toUtf8().data());
    weaver.serialize(ofs);
    ofs.close();
}

void MainWindow::on_actionAdd_node_triggered()
{
    dialogAddNode->show();
}

void MainWindow::createNode(QString name, double x, double y)
{
    weaver.addNode(QtAdapter::qstr2str(name), "core_node", x, y);
    nodesTreeShow();
    toJsNodeShow();
}

void MainWindow::nodesTreeShow()
{
    QTreeWidget* nodeTree = ui->treeWidgetNode;
    nodeTree->clear();// 清理全部节点
    QIcon icon;
    icon.addFile(":/img/exchange_node.png"); //设置ICON的图标
    for(size_t i = 0; i < weaver.nodeSize(); i++){
        QTreeWidgetItem* item = new QTreeWidgetItem(nodeTree, QTreeWidgetItem::Type); // 默认类型
        item->setIcon(0, icon);// 图标
        item->setText(0, QtAdapter::str2qstr(weaver.getNode(i).name()));// 节点名称
        item->setData(1, Qt::EditRole, QVariant(weaver.getNode(i).x()));// x坐标
        item->setData(2, Qt::EditRole, QVariant(weaver.getNode(i).y()));// y坐标
    }
    // 设置双击可编辑
    connect(nodeTree, &QTreeWidget::itemDoubleClicked, this, [=](QTreeWidgetItem* item, int column){
        nodeTree->openPersistentEditor(item, column);
    });
    // 设置编辑保存(enter)
    connect(nodeTree,  &QTreeWidget::itemActivated, this, [=](QTreeWidgetItem* item, int column){
        nodeTree->closePersistentEditor(item, column);
        size_t index = nodeTree->indexOfTopLevelItem(item);
        switch (column) {
        case 0:
            weaver.getNode(index).setName(QtAdapter::qstr2str(item->text(0)));
            break;
        case 1:
        case 2:
            weaver.getNode(index).move(item->data(1, Qt::EditRole).toDouble(), item->data(2, Qt::EditRole).toDouble());
        default:
            break;
        }
    });
}

void MainWindow::linksTreeShow()
{
    QTreeWidget* linkTree = ui->treeWidgetLink;
    linkTree->clear();
    QIcon icon;
    icon.addFile(":/img/optical_fiber.png"); //设置ICON的图标
    QIcon icon2;
    icon2.addFile(":/img/more.png");
    for(size_t i = 0; i < weaver.linkSize(); i++){
        QTreeWidgetItem* item = new QTreeWidgetItem(linkTree, QTreeWidgetItem::Type); // 默认类型
        item->setIcon(0, icon);// 图标
        item->setText(0, QtAdapter::str2qstr(weaver.getLink(i).name()));// 节点名称
        item->setText(1, QtAdapter::str2qstr(weaver.getLink(i).fromPtr()->name()));// 起点
        item->setText(2, QtAdapter::str2qstr(weaver.getLink(i).toPtr()->name()));// 终点
        item->setData(3, Qt::EditRole, QVariant(weaver.getLink(i).length()));// 长度
        item->setData(4, Qt::EditRole, QVariant(weaver.getLink(i).size()));// 光纤数量
        item->setIcon(5, icon2);// 更多
    }
    // 设置双击可编辑
    connect(linkTree, &QTreeWidget::itemDoubleClicked, this, [=](QTreeWidgetItem* item, int column){
        if(column == 1 || column == 2 || column == 5){

        }else{
            linkTree->openPersistentEditor(item, column);
        }
    });
    // 设置编辑保存(enter)
    connect(linkTree, &QTreeWidget::itemActivated, this, [=](QTreeWidgetItem* item, int column){
        linkTree->closePersistentEditor(item, column);
        size_t index = linkTree->indexOfTopLevelItem(item);
        switch (column) {
        case 0:
            weaver.getLink(index).setName(QtAdapter::qstr2str(item->text(0)));
            break;
        case 3:
            weaver.getLink(index).setLength(item->data(3, Qt::EditRole).toDouble());
            break;
        case 4:
            weaver.getLink(index).setSize(item->data(4, Qt::EditRole).toInt());
            break;
        default:
            break;
        }
    });
    // 设置单击更多图标显示更多对话框
    connect(linkTree, &QTreeWidget::itemClicked, this, [=](QTreeWidgetItem* item, int column){
        if(column == 5){
            size_t index = linkTree->indexOfTopLevelItem(item);// 获取坐标
            delete dialogLinkRes;
            dialogLinkRes = new DialogLinkRes(this);
            dialogLinkRes->load(weaver.getLink(index));
            dialogLinkRes->show();
        }
    });
}

void MainWindow::toJsNodeShow()
{
    // 更新显示节点信息
    QString str = "[";
    bool flag = true;
    for(size_t i = 0; i < weaver.nodeSize(); i++){
        if(flag){
            str = str + QString("{name:'%1',value:[%2,%3]}").arg(QtAdapter::str2qstr(weaver.getNode(i).name())).arg(weaver.getNode(i).x()).arg(weaver.getNode(i).y());
            flag = false;
        }else{
            str = str + QString(",{name:'%1',value:[%2,%3]}").arg(QtAdapter::str2qstr(weaver.getNode(i).name())).arg(weaver.getNode(i).x()).arg(weaver.getNode(i).y());
        }
    }
    str = str + "]";
    qDebug() << str;
    ui->webWidget->page()->runJavaScript(QString("upDateNodes(%1);").arg(str));
}

void MainWindow::toJsLinkShow()
{
    QString str = "[";
    bool flag = true;
    for(size_t i = 0; i < weaver.linkSize(); i++){
        if(flag){
            flag = false;
            str = str + QString("{fromName: '%1',toName: '%2',coords: [[%3,%4], [%5,%6]], name:'%7'}")
                .arg(QtAdapter::str2qstr(weaver.getLink(i).fromPtr()->name()))
                .arg(QtAdapter::str2qstr(weaver.getLink(i).toPtr()->name()))
                .arg(weaver.getLink(i).fromPtr()->x())
                .arg(weaver.getLink(i).fromPtr()->y())
                .arg(weaver.getLink(i).toPtr()->x())
                .arg(weaver.getLink(i).toPtr()->y())
                .arg(QtAdapter::str2qstr(weaver.getLink(i).name()));

        }else{
            str = str + QString(",{fromName: '%1',toName: '%2',coords: [[%3,%4], [%5,%6]], name:'%7'}")
                .arg(QtAdapter::str2qstr(weaver.getLink(i).fromPtr()->name()))
                .arg(QtAdapter::str2qstr(weaver.getLink(i).toPtr()->name()))
                .arg(weaver.getLink(i).fromPtr()->x())
                .arg(weaver.getLink(i).fromPtr()->y())
                .arg(weaver.getLink(i).toPtr()->x())
                .arg(weaver.getLink(i).toPtr()->y())
                .arg(QtAdapter::str2qstr(weaver.getLink(i).name()));
        }
    }
    str = str + "]";
    qDebug() << str;
    ui->webWidget->page()->runJavaScript(QString("upDateLinks(%1);").arg(str));
}

void MainWindow::toJsVNodeShow()
{
    // 更新显示节点信息
    QString str = "[";
    bool flag = true;
    for(size_t i = 0; i < weaver.virtualNodes().size(); i++){
        if(flag){
            str = str + QString("{name:'%1',value:[%2,%3]}").arg(QtAdapter::str2qstr(weaver.virtualNodes()[i]->name())).arg(weaver.virtualNodes()[i]->x()).arg(weaver.virtualNodes()[i]->y());
            flag = false;
        }else{
            str = str + QString(",{name:'%1',value:[%2,%3]}").arg(QtAdapter::str2qstr(weaver.virtualNodes()[i]->name())).arg(weaver.virtualNodes()[i]->x()).arg(weaver.virtualNodes()[i]->y());
        }
    }
    str = str + "]";
    qDebug() << "_____vnode______";
    qDebug() << str;
    ui->webWidget->page()->runJavaScript(QString("upDateVNodes(%1);").arg(str));
}

void MainWindow::toJsVLinkShow()
{
    /*
    // 以追加的形式添加虚拟链路
    ui->webWidget->page()->runJavaScript(QString("vLinksClear();"));// 清理原来的
    size_t offSize = 1000;
    for(size_t k = 0; k < weaver.virtualLinks().size(); k += offSize){
        QString str = "[";
        bool flag = true;
        size_t limit = k + offSize;
        for(size_t i = k; i < weaver.virtualLinks().size() && i < limit; i+=10){
            if(flag){
                flag = false;
                str = str + QString("{fromName: '%1',toName: '%2',coords: [[%3,%4], [%5,%6]], name:'%7-%8'}")
                    .arg(QtAdapter::str2qstr(weaver.virtualLinks()[i]->fromPtr()->name()))
                    .arg(QtAdapter::str2qstr(weaver.virtualLinks()[i]->toPtr()->name()))
                    .arg(weaver.virtualLinks()[i]->fromPtr()->x())
                    .arg(weaver.virtualLinks()[i]->fromPtr()->y())
                    .arg(weaver.virtualLinks()[i]->toPtr()->x())
                    .arg(weaver.virtualLinks()[i]->toPtr()->y())
                    .arg(QtAdapter::str2qstr(weaver.virtualLinks()[i]->name()))
                    .arg(i);

            }else{
                str = str + QString(",{fromName: '%1',toName: '%2',coords: [[%3,%4], [%5,%6]], name:'%7-%8'}")
                    .arg(QtAdapter::str2qstr(weaver.virtualLinks()[i]->fromPtr()->name()))
                    .arg(QtAdapter::str2qstr(weaver.virtualLinks()[i]->toPtr()->name()))
                    .arg(weaver.virtualLinks()[i]->fromPtr()->x())
                    .arg(weaver.virtualLinks()[i]->fromPtr()->y())
                    .arg(weaver.virtualLinks()[i]->toPtr()->x())
                    .arg(weaver.virtualLinks()[i]->toPtr()->y())
                    .arg(QtAdapter::str2qstr(weaver.virtualLinks()[i]->name()))
                    .arg(i);
            }
        }

        str = str + "]";
        ui->webWidget->page()->runJavaScript(QString("addEndDateVLinks(%1);").arg(str));
    }
    qDebug() << "v-link finish";
    */
    ui->webWidget->page()->runJavaScript(QString("vLinksClear();"));// 清理原来的
    QString str = "[";
    bool flag = true;
    for(size_t i = 0; i < weaver.linkSize(); i++){
        if(flag){
            flag = false;
            str = str + QString("{fromName: '%1',toName: '%2',coords: [[%3,%4], [%5,%6]], name:'%7'}")
                .arg(QtAdapter::str2qstr(weaver.getLink(i).fromPtr()->name()))
                .arg(QtAdapter::str2qstr(weaver.getLink(i).toPtr()->name()))
                .arg(weaver.getLink(i).fromPtr()->x())
                .arg(weaver.getLink(i).fromPtr()->y())
                .arg(weaver.getLink(i).toPtr()->x())
                .arg(weaver.getLink(i).toPtr()->y())
                .arg(QtAdapter::str2qstr(weaver.getLink(i).name()));

        }else{
            str = str + QString(",{fromName: '%1',toName: '%2',coords: [[%3,%4], [%5,%6]], name:'%7'}")
                .arg(QtAdapter::str2qstr(weaver.getLink(i).fromPtr()->name()))
                .arg(QtAdapter::str2qstr(weaver.getLink(i).toPtr()->name()))
                .arg(weaver.getLink(i).fromPtr()->x())
                .arg(weaver.getLink(i).fromPtr()->y())
                .arg(weaver.getLink(i).toPtr()->x())
                .arg(weaver.getLink(i).toPtr()->y())
                .arg(QtAdapter::str2qstr(weaver.getLink(i).name()));
        }
    }
    str = str + "]";
    qDebug() << str;
    ui->webWidget->page()->runJavaScript(QString("addEndDateVLinks(%1);").arg(str));
}

void MainWindow::on_actionAdd_link_triggered()
{
    // 更新节点
    QStringList strList;
    for(size_t i=0; i < weaver.nodeSize(); i++){
        QString name = QtAdapter::str2qstr(weaver.getNode(i).name());
        strList << name;
    }
    dialogAddFiberLink->updateNodeList(strList);
    dialogAddFiberLink->show();
}

void MainWindow::createFiberLink(QString name, int from, int to, int size, double length)
{
    weaver.addLink(QtAdapter::qstr2str(name), "fiber_link", length, size, from, to);
    linksTreeShow();
    toJsLinkShow();
}

void MainWindow::on_actionexit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionmap_triggered()
{
    weaver.virtualMap();
    // 虚拟化映射后显示到屏幕上
    // 更新虚拟节点到web
    toJsVNodeShow();
    // 更新虚拟链路到web
    toJsVLinkShow();
}

void MainWindow::on_actionConfig_triggered()
{
    dialogPlaySimulator->load(simulator);
    dialogPlaySimulator->show();
}

void MainWindow::on_actionPlay_triggered()
{
    dialogReault->load(simulator, weaver);
    //weaver.virtualMap();
    //simulator.begin(weaver);
    dialogReault->show();
    dialogReault->begin();

}
