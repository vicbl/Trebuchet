#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H
#include<QString>
#include <QDialog>

namespace Ui {
class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget *parent);
    QString getName();
    int getDifficulty();
    ~NewGameDialog();

private:
    Ui::NewGameDialog *ui;
};

#endif // NEWGAMEDIALOG_H
