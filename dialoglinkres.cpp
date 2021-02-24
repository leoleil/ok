#include <QTreeWidget>
#include <QIcon>
#include <QTreeWidgetItem>
#include <QDebug>
#include "dialoglinkres.h"
#include "ui_dialoglinkres.h"

DialogLinkRes::DialogLinkRes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLinkRes)
{
    ui->setupUi(this);
}

DialogLinkRes::~DialogLinkRes()
{
    delete ui;
}

void DialogLinkRes::load(FiberLink &link)
{
    fiberLink = &link;
    QTreeWidget* treeWidget = ui->treeWidget;// 清理目录
    treeWidget->collapseAll();
    treeWidget->clear();
    // 加载各个光纤情况
    for(size_t i = 0; i < fiberLink->size(); i++){
        // 加载列表
        QTreeWidgetItem* linkItem = new QTreeWidgetItem(treeWidget, QTreeWidgetItem::Type);
        linkItem->setText(0, QString::number(i,10) + ". 光纤");// 光纤
        QTreeWidgetItem* fiberRateItem = new QTreeWidgetItem(linkItem, QTreeWidgetItem::Type);// 速率
        fiberRateItem->setText(0, "速率(Hz)");
        fiberRateItem->setData(1, Qt::EditRole, QVariant((*fiberLink)[i].rate()));
        QTreeWidgetItem* fiberModeItem = new QTreeWidgetItem(linkItem, QTreeWidgetItem::Type);// 模式数量
        fiberModeItem->setText(0, "模式数量");
        fiberModeItem->setData(1, Qt::EditRole, QVariant((*fiberLink)[i].modelSize()));
        QTreeWidgetItem* fiberWaverItem = new QTreeWidgetItem(linkItem, QTreeWidgetItem::Type);// 波段数量
        fiberWaverItem->setText(0, "波段数量");
        fiberWaverItem->setData(1, Qt::EditRole, QVariant((*fiberLink)[i].weaverSize()));
        QTreeWidgetItem* fiberRateSizeItem = new QTreeWidgetItem(linkItem, QTreeWidgetItem::Type);// 波段数量
        fiberRateSizeItem->setText(0, "频隙数量");
        fiberRateSizeItem->setData(1, Qt::EditRole, QVariant((*fiberLink)[i].rateSize()));
        QTreeWidgetItem* fiberCoreItem = new QTreeWidgetItem(linkItem, QTreeWidgetItem::Type);// 核心数量
        fiberCoreItem->setText(0, "纤芯数量");
        fiberCoreItem->setData(1, Qt::EditRole, QVariant((*fiberLink)[i].coreSize()));
        // 加载每个核心情况
        for(size_t j = 0; j < fiberLink->at(i).coreSize(); j++){
            // 加载每个核心的波段情况
            QTreeWidgetItem* fiberCoreInfoItem = new QTreeWidgetItem(fiberCoreItem, QTreeWidgetItem::Type);// 波段数量
            fiberCoreInfoItem->setText(0, QString::number(j) + ".纤芯");
            // 加载波段
            for(size_t k = 0; k < (*fiberLink)[i][j].wavelengths.size(); k++){
                // 加载每个核心的波段情况
                QTreeWidgetItem* fiberWaverCoreItem = new QTreeWidgetItem(fiberCoreInfoItem, QTreeWidgetItem::Type);// 波段数量
                fiberWaverCoreItem->setText(0, QString::number(k) + ".波段");
                QTreeWidgetItem* waverLength = new QTreeWidgetItem(fiberWaverCoreItem, QTreeWidgetItem::Type);// 波长
                waverLength->setText(0, "波长");
                waverLength->setData(1, Qt::EditRole, QVariant((*fiberLink)[i][j].wavelengths[k].length()));
            }
        }

    }
    // 设置双击编辑
    connect(treeWidget, &QTreeWidget::itemDoubleClicked, this, [=](QTreeWidgetItem* item, int column){
       if(column == 1){
           treeWidget->openPersistentEditor(item, column);
       }

    });
    // 设置编辑保存(enter)
    connect(treeWidget, &QTreeWidget::itemActivated, this, [=](QTreeWidgetItem* item, int column){
        treeWidget->closePersistentEditor(item, column);
        if(item->text(0) == "速率(Hz)"){
            int index = treeWidget->indexOfTopLevelItem(item->parent());// 获取坐标
            (*fiberLink)[index].setRate(item->data(1, Qt::EditRole).toDouble());//设置带宽
        }
        if(item->text(0) == "模式数量"){
            int index = treeWidget->indexOfTopLevelItem(item->parent());// 获取坐标
            (*fiberLink)[index].setModelSize(item->data(1, Qt::EditRole).toInt());//设置模式数量
        }
        if(item->text(0) == "波段数量"){
            int index = treeWidget->indexOfTopLevelItem(item->parent());// 获取坐标
            (*fiberLink)[index].setWeaverSize(item->data(1, Qt::EditRole).toInt());//设置波段数量
            reloadWavelengthItem(index);
        }
        if(item->text(0) == "纤芯数量"){
            int index = treeWidget->indexOfTopLevelItem(item->parent());// 获取坐标
            (*fiberLink)[index].setCoreSize(item->data(1, Qt::EditRole).toInt());//设置纤芯数量
            reloadWavelengthItem(index);
        }
        if(item->text(0) == "频隙数量"){
            int index = treeWidget->indexOfTopLevelItem(item->parent());// 获取坐标
            (*fiberLink)[index].setRateSize(item->data(1, Qt::EditRole).toInt());
        }
        if(item->text(0) == "波长"){
            int i = treeWidget->indexOfTopLevelItem(item->parent()->parent()->parent()->parent());// 获取坐标
            int j = item->parent()->parent()->parent()->indexOfChild(item->parent()->parent());
            int k = item->parent()->parent()->indexOfChild(item->parent());
            (*fiberLink)[i][j].wavelengths[k].setLength(item->data(1, Qt::EditRole).toDouble());
        }

    });
}

void DialogLinkRes::reload()
{
    QTreeWidget* treeWidget = ui->treeWidget;// 清理目录
    treeWidget->collapseAll();
    treeWidget->clear();
    // 加载各个光纤情况
    for(size_t i = 0; i < fiberLink->size(); i++){
        // 加载列表
        QTreeWidgetItem* linkItem = new QTreeWidgetItem(treeWidget, QTreeWidgetItem::Type);
        linkItem->setText(0, QString::number(i,10) + ". 光纤");// 光纤
        QTreeWidgetItem* fiberRateItem = new QTreeWidgetItem(linkItem, QTreeWidgetItem::Type);// 速率
        fiberRateItem->setText(0, "速率(Hz)");
        fiberRateItem->setData(1, Qt::EditRole, QVariant((*fiberLink)[i].rate()));
        QTreeWidgetItem* fiberModeItem = new QTreeWidgetItem(linkItem, QTreeWidgetItem::Type);// 模式数量
        fiberModeItem->setText(0, "模式数量");
        fiberModeItem->setData(1, Qt::EditRole, QVariant((*fiberLink)[i].modelSize()));
        QTreeWidgetItem* fiberWaverItem = new QTreeWidgetItem(linkItem, QTreeWidgetItem::Type);// 波段数量
        fiberWaverItem->setText(0, "波段数量");
        fiberWaverItem->setData(1, Qt::EditRole, QVariant((*fiberLink)[i].weaverSize()));
        QTreeWidgetItem* fiberCoreItem = new QTreeWidgetItem(linkItem, QTreeWidgetItem::Type);// 核心数量
        fiberCoreItem->setText(0, "纤芯数量");
        fiberCoreItem->setData(1, Qt::EditRole, QVariant((*fiberLink)[i].coreSize()));
        // 加载每个核心情况
        for(size_t j = 0; j < fiberLink->at(i).coreSize(); j++){
            // 加载每个核心的波段情况
            QTreeWidgetItem* fiberCoreInfoItem = new QTreeWidgetItem(fiberCoreItem, QTreeWidgetItem::Type);// 波段数量
            fiberCoreInfoItem->setText(0, QString::number(j) + ".纤芯");
            // 加载波段
            for(size_t k = 0; k < (*fiberLink)[i][j].wavelengths.size(); k++){
                // 加载每个核心的波段情况
                QTreeWidgetItem* fiberWaverCoreItem = new QTreeWidgetItem(fiberCoreInfoItem, QTreeWidgetItem::Type);// 波段数量
                fiberWaverCoreItem->setText(0, QString::number(k) + ".波段");
                QTreeWidgetItem* waverLength = new QTreeWidgetItem(fiberWaverCoreItem, QTreeWidgetItem::Type);// 波长
                waverLength->setText(0, "波长");
                waverLength->setData(1, Qt::EditRole, QVariant((*fiberLink)[i][j].wavelengths[k].length()));
            }
        }

    }
}

void DialogLinkRes::reloadWavelengthItem(int i)
{
    QTreeWidget* treeWidget = ui->treeWidget;
    QTreeWidgetItem* fiberCoreItem = treeWidget->topLevelItem(i)->child(4);// 定位
    // 移除之前的
    while(fiberCoreItem->childCount() != 0){
        QTreeWidgetItem * child  = fiberCoreItem->takeChild(0);
        delete child;
        child = nullptr;
    }

    // 加载每个核心情况
    for(size_t j = 0; j < fiberLink->at(i).coreSize(); j++){
        // 加载每个核心的波段情况
        QTreeWidgetItem* fiberCoreInfoItem = new QTreeWidgetItem(fiberCoreItem, QTreeWidgetItem::Type);// 各个纤芯
        fiberCoreInfoItem->setText(0, QString::number(j) + ".纤芯");
        // 加载波段
        for(size_t k = 0; k < (*fiberLink)[i][j].wavelengths.size(); k++){
            // 加载每个核心的波段情况
            QTreeWidgetItem* fiberWaverCoreItem = new QTreeWidgetItem(fiberCoreInfoItem, QTreeWidgetItem::Type);// 波段数量
            fiberWaverCoreItem->setText(0, QString::number(k) + ".波段");
            QTreeWidgetItem* waverLength = new QTreeWidgetItem(fiberWaverCoreItem, QTreeWidgetItem::Type);// 波长
            waverLength->setText(0, "波长");
            waverLength->setData(1, Qt::EditRole, QVariant((*fiberLink)[i][j].wavelengths[k].length()));
        }
    }
}
