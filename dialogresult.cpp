#include "dialogresult.h"
#include "ui_dialogresult.h"

DialogResult::DialogResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogResult)
{
    ui->setupUi(this);
    threadPtr = new MyThread();
}

DialogResult::~DialogResult()
{
    delete ui;
    delete threadPtr;
}

void DialogResult::load(Simulator &simulator, Weaver &weaver)
{
    simulatorPtr = &simulator;
    threadPtr->load(simulator, weaver);
}


void DialogResult::begin()
{
    if(simulatorPtr == nullptr){
        return;
    }
    ui->progressBar->setRange(0, simulatorPtr->getCount());
    ui->progressBar->setValue(0);
    threadPtr->start();
    while(simulatorPtr->getNowCount() < simulatorPtr->getCount()){
        QCoreApplication::processEvents();//避免界面冻结
        ui->progressBar->setValue(simulatorPtr->getNowCount());
        QThread::sleep(1);
    }
    ui->progressBar->setValue(simulatorPtr->getCount());
    ui->label_all_time->setNum((int)simulatorPtr->getOverallResponseTime());
    ui->label_block_num->setNum((int)simulatorPtr->getBlockTrafficQueue().size());
    ui->label_fail_time->setNum((int)simulatorPtr->getTrafficBlockOverallResponseTime());
    ui->label_traffic_num->setNum((int)simulatorPtr->getTrafficNum());
    ui->label_success_time->setNum((int)simulatorPtr->getTrafficSuccessOverallResponseTime());
}

MyThread::MyThread(){

}

void MyThread::load(Simulator &simulator, Weaver &weaver)
{
    this->weaver = &weaver;
    this->simulator = &simulator;
}


void MyThread::run()
{
    simulator->begin(*weaver);
}
