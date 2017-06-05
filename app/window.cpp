// window.cpp

#include <QtWidgets>
#include "window.h"
#include "ui_window.h"
#include <QDebug>
#include <QTime>

#include "myglwidget.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    connect(ui->myGLWidget, SIGNAL(xRotationChanged(int)), ui->rotXSlider, SLOT(setValue(int)));
    connect(ui->myGLWidget, SIGNAL(yRotationChanged(int)), ui->rotYSlider, SLOT(setValue(int)));
    connect(ui->myGLWidget, SIGNAL(zRotationChanged(int)), ui->rotZSlider, SLOT(setValue(int)));
    connect(ui->myGLWidget, SIGNAL(forceChanged(int)), ui->forceSlider, SLOT(setValue(int)));
    connect(ui->myGLWidget, SIGNAL(chrono1Refresh(QString)), ui->chronoPartie, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(chrono2Refresh(QString)), ui->chronoTotal, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setName(QString)), ui->name, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setDifficulty(QString)), ui->difficulty, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setScore(QString)), ui->score, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setNbCibles(QString)), ui->nbCibles, SLOT(setText(QString)));


     connect(ui->myGLWidget, SIGNAL(disableButton(bool)), ui->lancerBouton, SLOT(setEnabled(bool)));
    //Meilleur scores
    connect(ui->myGLWidget, SIGNAL(setBestName1(QString)), ui->bestName1, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setBestName2(QString)), ui->bestName2, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setBestName3(QString)), ui->bestName3, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setBestName4(QString)), ui->bestName4, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setBestName5(QString)), ui->bestName5, SLOT(setText(QString)));

    connect(ui->myGLWidget, SIGNAL(setBestScore1(QString)), ui->bestScore1, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setBestScore2(QString)), ui->bestScore2, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setBestScore3(QString)), ui->bestScore3, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setBestScore4(QString)), ui->bestScore4, SLOT(setText(QString)));
    connect(ui->myGLWidget, SIGNAL(setBestScore5(QString)), ui->bestScore5, SLOT(setText(QString)));




    connect(this, SIGNAL(on_lancerBouton_clicked()), ui->myGLWidget, SLOT(lancerBoutonClicked()));
    connect(this, SIGNAL(on_startButton_clicked()), ui->myGLWidget, SLOT(startButton_clicked()));
    connect(this, SIGNAL(on_vueSuivie_stateChanged()), ui->myGLWidget, SLOT(vueChanged()));
    connect(this, SIGNAL(on_trajectory_stateChanged()), ui->myGLWidget, SLOT(trajectoryActived()));
    connect(this, SIGNAL(on_nightMode_stateChanged()), ui->myGLWidget, SLOT(nightModeActived()));
}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Z){
        int xScene=ui->myGLWidget->getXScene()+1;
        if (xScene<100 && xScene>-70)
        {
            ui->myGLWidget->setXScene(xScene);
            ui->myGLWidget-> updateGL();
        }
    }
    if (event->key() == Qt::Key_Q){
        int zScene=ui->myGLWidget->getZScene()-1;
        ui->myGLWidget->setZScene(zScene);
        ui->myGLWidget->xRotationChanged(zScene);
        ui->myGLWidget-> updateGL();
    }
    if (event->key() == Qt::Key_S){
        int xScene=ui->myGLWidget->getXScene()-1;
        if (xScene<100 && xScene>-70)
        {
            ui->myGLWidget->setXScene(xScene);
            ui->myGLWidget-> updateGL();
        }
    }
    if (event->key() == Qt::Key_D){
        int zScene=ui->myGLWidget->getZScene()+1;
        ui->myGLWidget->setZScene(zScene);
        ui->myGLWidget->xRotationChanged(zScene);
        ui->myGLWidget-> updateGL();
    }
    if (event->key() == Qt::Key_A){
        int zoomScene=ui->myGLWidget->getZoomScene()-1;
        ui->myGLWidget->setZoomScene(zoomScene);
        ui->myGLWidget-> updateGL();
    }
    if (event->key() == Qt::Key_E){
        int zoomScene=ui->myGLWidget->getZoomScene()+1;
        ui->myGLWidget->setZoomScene(zoomScene);

        ui->myGLWidget-> updateGL();
    }
    // Recentrer derrière le trébuchet
    if (event->key() == Qt::Key_C){
        ui->myGLWidget->recentrer();
    }
}

void Window::on_forceSlider_valueChanged(int value)
{
    ui->myGLWidget->setForce(value);
}
