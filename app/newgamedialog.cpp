#include "newgamedialog.h"
#include "ui_newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameDialog)
{
    ui->setupUi(this);
}

QString NewGameDialog::getName()
{
    return ui->_nomJoueur->text();
}

int NewGameDialog::getDifficulty()
{
    if(ui->radioButton->isChecked())
    {
        return 1;
    }else if(ui->radioButton_2->isChecked()){
        return 2;
    }else if(ui->radioButton_3->isChecked()){
        return 3;
    }else if(ui->radioButton_4->isChecked()){
        return 4;
    }else if(ui->radioButton_5->isChecked()){
        return 5;
    }else {
        return 0;
    }
}
NewGameDialog::~NewGameDialog()
{
    delete ui;
}
