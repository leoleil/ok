#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "dialogaddnode.h"
#include "ui_dialogaddnode.h"

DialogAddNode::DialogAddNode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddNode)
{
    ui->setupUi(this);
}

DialogAddNode::~DialogAddNode()
{
    delete ui;
}

void DialogAddNode::on_buttonBox_accepted()
{
    QString nodeName = ui->lineEditNodeName->text();
    double x = ui->doubleSpinBoxNodeX->value();
    double y = ui->doubleSpinBoxNodeY->value();
    if(nodeName.isEmpty()){
        QMessageBox::warning(this, QString("Warning"), QString("Please input the name."), QMessageBox::Ok,QMessageBox::NoButton);
    }
    else{
        qDebug() << nodeName << " x:" << x << " y:" << y;
        emit createNode(nodeName, x, y);// 发送创建节点的信号
    }
}
