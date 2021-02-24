#include "dialogplaysimulator.h"
#include "ui_dialogplaysimulator.h"

DialogPlaySimulator::DialogPlaySimulator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPlaySimulator)
{
    ui->setupUi(this);
}

DialogPlaySimulator::~DialogPlaySimulator()
{
    delete ui;
}

void DialogPlaySimulator::load(Simulator &simulator)
{
    simulatorPtr = &simulator;
}

void DialogPlaySimulator::on_buttonBox_accepted()
{
    if(simulatorPtr == nullptr){
        return;
    }
    int lambda1;
    double lambda2;
    int count;
    size_t tNum;
    lambda1 = ui->spinBoxLambda1->value();
    lambda2 = ui->doubleSpinBoxLambda2->value();
    count = ui->spinBoxCount->value();
    tNum = ui->spinBoxTread->value();
    simulatorPtr->setCount(count);
    simulatorPtr->setPoissonLambda(lambda1);
    simulatorPtr->setExponentialLambda(lambda2);
    simulatorPtr->setThreadNum(tNum);
}
