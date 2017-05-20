// window.cpp

#include <QtWidgets>
#include "window.h"
#include "ui_window.h"
#include <QDebug>

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
    connect(this, SIGNAL(on_lancerBouton_clicked()), ui->myGLWidget, SLOT(lancerBoutonClicked()));
    connect(this, SIGNAL(on_Webcam_clicked()), ui->myGLWidget, SLOT(webcam_clicked()));
    connect(this, SIGNAL(on_jouer_clicked()), ui->myGLWidget, SLOT(jouer_clicked()));

}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Z){
        qDebug()<<"Z";
        int xScene=ui->myGLWidget->getXScene()+1;
       /* if (xScene<-90 && xScene>-270)
        {

        }*/
 ui->myGLWidget->setXScene(xScene);
        ui->myGLWidget-> updateGL();
        qDebug()<<xScene;
    }
    if (event->key() == Qt::Key_Q){
        qDebug()<<"Q";
        int zScene=ui->myGLWidget->getZScene()-1;
        ui->myGLWidget->setZScene(zScene);
        ui->myGLWidget->xRotationChanged(zScene);
        ui->myGLWidget-> updateGL();
        qDebug()<<zScene;
    }
    if (event->key() == Qt::Key_S){
        qDebug()<<"S";
        int xScene=ui->myGLWidget->getXScene()-1;
       // if (xScene<-90 && xScene>-270)
     //   {
            ui->myGLWidget->setXScene(xScene);
      //z  }
        ui->myGLWidget-> updateGL();
        qDebug()<<xScene;
    }
    if (event->key() == Qt::Key_D){
        qDebug()<<"D";
        int zScene=ui->myGLWidget->getZScene()+1;
        ui->myGLWidget->setZScene(zScene);
        ui->myGLWidget->xRotationChanged(zScene);
        ui->myGLWidget-> updateGL();
        qDebug()<<zScene;
    }
    if (event->key() == Qt::Key_A){
        qDebug()<<"A";
        int zoomScene=ui->myGLWidget->getZoomScene()-1;
        ui->myGLWidget->setZoomScene(zoomScene);
        ui->myGLWidget-> updateGL();
        qDebug()<<zoomScene;
    }
    if (event->key() == Qt::Key_E){
        qDebug()<<"E";
        int zoomScene=ui->myGLWidget->getZoomScene()+1;
        ui->myGLWidget->setZoomScene(zoomScene);

        ui->myGLWidget-> updateGL();
        qDebug()<<zoomScene;
    }
}

