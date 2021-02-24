#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "dialogaddfiberlink.h"
#include "ui_dialogaddfiberlink.h"

DialogAddFiberLink::DialogAddFiberLink(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddFiberLink)
{
    ui->setupUi(this);
}

DialogAddFiberLink::~DialogAddFiberLink()
{
    delete ui;
}

void DialogAddFiberLink::updateNodeList(QStringList qstrList)
{
    ui->comboBoxFrom->clear();
    ui->comboBoxTo->clear();
    ui->comboBoxFrom->addItems(qstrList);
    ui->comboBoxTo->addItems(qstrList);
}

void DialogAddFiberLink::on_buttonBox_accepted()
{
    QString name = ui->lineEditLink->text();
    int from = ui->comboBoxFrom->currentIndex();
    int to = ui->comboBoxTo->currentIndex();
    int size = ui->spinBoxFiberSize->value();
    double length = ui->doubleSpinBoxLength->value();
    // 输入校验
    if(name.isEmpty()){
        QMessageBox::warning(this, QString("Warning"), QString("Please input the name."), QMessageBox::Ok,QMessageBox::NoButton);
    }
    else if(from == -1){
        QMessageBox::warning(this, QString("Warning"), QString("Please choose from node."), QMessageBox::Ok,QMessageBox::NoButton);
    }
    else if(to == -1){
        QMessageBox::warning(this, QString("Warning"), QString("Please choose from node."), QMessageBox::Ok,QMessageBox::NoButton);
    }
    else{
        emit createFiberLink(name, from, to, size, length);
    }
}

