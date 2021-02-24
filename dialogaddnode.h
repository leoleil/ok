#ifndef DIALOGADDNODE_H
#define DIALOGADDNODE_H

#include <QDialog>

namespace Ui {
class DialogAddNode;
}

class DialogAddNode : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddNode(QWidget *parent = 0);
    ~DialogAddNode();

signals:
    void createNode(QString name, double x, double y);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogAddNode *ui;
};

#endif // DIALOGADDNODE_H
