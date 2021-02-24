#ifndef DIALOGADDFIBERLINK_H
#define DIALOGADDFIBERLINK_H

#include <QDialog>
#include <QStringList>
namespace Ui {
class DialogAddFiberLink;
}

class DialogAddFiberLink : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddFiberLink(QWidget *parent = 0);
    ~DialogAddFiberLink();
    void updateNodeList(QStringList qstrList);

signals:
    void createFiberLink(QString name, int from, int to, int size, double length);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogAddFiberLink *ui;
};

#endif // DIALOGADDFIBERLINK_H
