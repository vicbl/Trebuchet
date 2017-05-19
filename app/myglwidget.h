// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <GL/glu.h>

#include"webcam.h"
class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();


    int getXScene();
    int getYScene();
    int getZScene();
    int getZoomScene();

    void setXScene(int x);
    void setYScene(int y);
    void setZScene(int z);
    void setZoomScene(int zoom);

signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    //void keyPressEvent ( QKeyEvent * event );
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setForce(int angle);
    void lancerBoutonClicked();
    void webcam_clicked();
    void setValue();

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void forceChanged(int angle);



private:
    void draw();
    void loadTextures();
    void reInitialize();
    void drawBoxBois();
    void drawPelouse();
    void drawLevierBois();
    void drawCorde();
    void drawTrebuchetComplet();
    void drawGrid();

    //Coordonnées de la scène globale
    int xScene_=-100;
    int yScene_=0;
    int zScene_=180;
    int zoomScene_=2;

    int xRot;
    int yRot;
    int zRot;

    int force;
    Webcam *w;

    int xBoulet;
    int yBoulet;

    int angle_;

    double angle1;
    double angle2;
    double angle3;
    double angle4;
    double angle5;

    GLuint boxBois;
    GLuint pelouse;
    GLuint levierBois;
    GLuint corde;
    GLuint trebuchetComplet;
    GLuint grid;
    GLuint gridPart;

    GLUquadric* corde1;

    boolean bouletLance_;
    boolean lancement_;

    GLuint texture[];

    QPoint lastPos;
};

#endif // MYGLWIDGET_H

