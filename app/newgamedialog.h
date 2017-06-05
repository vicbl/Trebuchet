#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H
#include<QString>
#include <QDialog>

/* classe : NewGameDialog
 * Ecrite par Victor Blanchard
 * Gère le contenu et les actions de la fenêtre de nouvelle partie
 */

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
