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
private:
    Ui::NewGameDialog *ui;

public:
    explicit NewGameDialog(QWidget *parent);
    QString getName();
    int getDifficulty();
    ~NewGameDialog();
};

#endif // NEWGAMEDIALOG_H
