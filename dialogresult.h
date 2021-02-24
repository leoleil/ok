#ifndef DIALOGRESULT_H
#define DIALOGRESULT_H

#include <QDialog>
#include <QThread>

#include "Simulator.h"

namespace Ui {
class DialogResult;
}


class MyThread: public QThread{
public:
    MyThread();
    void load(Simulator& simulator, Weaver& weaver);
    void run(); //声明继承于QThread虚函数 run()
private:
    Simulator* simulator;
    Weaver* weaver;
};

class DialogResult : public QDialog
{
    Q_OBJECT

public:
    explicit DialogResult(QWidget *parent = nullptr);
    ~DialogResult();
    void load(Simulator& simulator, Weaver& weaver);
    void begin();
private slots:


private:
    Ui::DialogResult *ui;
    Simulator* simulatorPtr;
    MyThread *threadPtr;
};

#endif // DIALOGRESULT_H
