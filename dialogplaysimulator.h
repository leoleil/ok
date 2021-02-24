#ifndef DIALOGPLAYSIMULATOR_H
#define DIALOGPLAYSIMULATOR_H

#include <QDialog>
#include "Simulator.h"
namespace Ui {
class DialogPlaySimulator;
}

class DialogPlaySimulator : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPlaySimulator(QWidget *parent = nullptr);
    ~DialogPlaySimulator();
    void load(Simulator& simulator);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogPlaySimulator *ui;
    Simulator* simulatorPtr = nullptr;
};

#endif // DIALOGPLAYSIMULATOR_H
