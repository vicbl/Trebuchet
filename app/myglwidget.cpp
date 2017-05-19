// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
//#include <QKeyEvent>
#include <iostream>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "myglwidget.h"
#include "ui_window.h"
#include <GL/glu.h>
#include <QDebug>
#include <cmath>
#include"webcam.h"
#include"textures.h"
using namespace std;

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = -20;
    zRot = 180;
    force = -20;

    xBoulet = 0;
    yBoulet = 0;

    angle_ = 0;
    angle1 = 3;
    angle2 = 5;
    angle3 = 9;
    angle4 = 14;
    angle5 = 19;

    w=new Webcam();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(setValue()));
    timer->start(10);

    bouletLance_ = false;
    lancement_ = false;

    // corde1 = gluNewQuadric();
}

MyGLWidget::~MyGLWidget()
{
}
void MyGLWidget::setValue()
{
    if (w->getActive()){
        zRot=w->getxPosition();
        yRot=w->getyPosition();
        qDebug()<<"x="<<xRot<<" y ="<<zRot;


        updateGL();
    }
}
// Fonction de 'sleep' : qSleep() appartient au module QtTest
static void delay(int tp)
{
    QTime dieTime= QTime::currentTime().addMSecs(tp); // Attend tp ms
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MyGLWidget::reInitialize()
{
    while (yRot>-20)
    {
        yRot--;
        int angle = yRot;
        emit yRotationChanged(angle);
        gluDeleteQuadric(corde1);
        // corde1 = gluNewQuadric();
        updateGL();

        delay(10);
    }
    force = 0;
}

int MyGLWidget::getXScene()
{
    return xScene_;
}
int MyGLWidget::getYScene()
{
    return yScene_;
}
int MyGLWidget::getZScene()
{
    return zScene_;
}
int MyGLWidget::getZoomScene()
{
    return zoomScene_;
}
void MyGLWidget::setXScene( int x)
{
    xScene_=x;
}
void MyGLWidget::setYScene( int y)
{
    yScene_=y;
}
void MyGLWidget::setZScene( int z)
{
    zScene_=z;
}
void MyGLWidget::setZoomScene( int zoom)
{
    zoomScene_=zoom;
}
QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(600, 600);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}



void MyGLWidget::lancerBoutonClicked()
{
    if (!lancement_)
    {

        // INITIALISATION

        lancement_=true;
        int final_xRot;     // xRot final pour être derrière le trébuchet
        int angle = xRot;   // Angle de rotation du trébuchet

        int vitesse = -force;   // V0 du boulet
        int angle_tir = 20;     // Angle a0 de V0 au départ du boulet
        int g = 1;              // Force g du poids
        int pos_treb = 0;       // position trigonométrique du trébuchet autour de son axe de rotation


        /*
         * zRot = angle = [100 - 180 - 260]
         * xRot = zone  = [80 - 0=360 - 280]
        */

        // ORIENTATION DE LA CAMERA
        if (zRot<=180)
        {
            final_xRot = 180-zRot;
        } else
        {
            final_xRot = 540-zRot; // 540 = 360 + 180
        }
        //qDebug(" - %d - %d", final_xRot, angle);
        while(final_xRot!=angle)
        {
            if (xRot<final_xRot)
            {
                angle++;
            } else
            {
                angle--;
            }

            qNormalizeAngle(angle);
            if (angle != xRot)
            {
                xRot = angle;
                emit xRotationChanged(angle);
                gluDeleteQuadric(corde1);
                // corde1 = gluNewQuadric();
                updateGL();
            }
            // qDebug(" - %d", angle);
            delay(15);
        }


        // FIN ORIENTATION DE LA CAMERA

        delay(600);

        // LANCEMENT

        while (pos_treb<420)
        {
            // chopper coordonées fin de la corde
            if (pos_treb<170)
            {
                yRot++;
                // qDebug("%d",yRot);
            } else if (pos_treb<265)
            {
                yRot--;
            } else if (pos_treb<325)
            {
                yRot++;
            } else if (pos_treb<370)
            {
                yRot--;
            } else if (pos_treb<400)
            {
                yRot++;
            } else if (pos_treb<415)
            {
                yRot--;
            }else
            {
                yRot++;
            }

            pos_treb++;

            angle = yRot;
            emit yRotationChanged(angle);
            gluDeleteQuadric(corde1);
            // corde1 = gluNewQuadric();
            updateGL();

            delay(12);
        }
        delay(1000);
        reInitialize();


    }
    lancement_=false;

}

void MyGLWidget::setForce(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot && !lancement_) {
        yRot = angle;
        force = angle;
        emit yRotationChanged(angle);
        emit forceChanged(angle);

        gluDeleteQuadric(corde1);
        // corde1 = gluNewQuadric();
        updateGL();
    }
}

void MyGLWidget::setXRotation(int angle) // Zone
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);

        gluDeleteQuadric(corde1);
        // corde1 = gluNewQuadric();

        updateGL();
    }

}

void MyGLWidget::setYRotation(int angle) // bascule trébuchet
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;

        force = angle;
        // emit yRotationChanged(angle);
    }

    if (!bouletLance_)
    {
        angle_ = round((angle+20)*3); // angle_ va de 0 à 360, puis lacher de boulet, puis oscille entre 540 et 180 jusquà arrêt

        angle1 = 3 - round(angle_/120); // [3 ; 0] (120 = 360/3)
        angle2 = 5 - round(angle_/72); // [5 ; 0] (72 = 360/5)
        angle3 = 9 - round(angle_/40); // [9 ; 0] (40 = 360/9)
        angle4 = 14 - round(angle_/28); // [14 ; 1] (28 = 360/13)
        angle5 = 19 - round(angle_/21); // [19 ; 2] (21 = 360/17)

        if (angle_ == 510)
        {
            bouletLance_=true;
        }
    } else
    {
        angle_ = round(angle); // angle_ va de -20 à 160

        if (angle_ > 130)
        {
            angle1 = -1*(angle_-145)/15; // [-1 ; 1]
            angle2 = -2*(angle_-145)/15; // [-2 ; 2]
            angle3 = -4*(angle_-145)/15; // [-3 ; 3]
            angle4 = -6*(angle_-145)/15; // [-5 ; 5] x4
            angle5 = -25+25*(angle_-145)/15;   // x2  -> de 0 à -50°
        }
        else {
            if (angle_ > 50)
            {
                angle1 = 4*(angle_-90)/40; //
                angle2 = 3*(angle_-90)/40; //
                angle3 = 2*(angle_-90)/40; //
                angle4 = 1*(angle_-90)/40; // x4
                angle5 = -90+(angle_-90); // x2  -> de -50 à -130

            } else
            {
                angle1 = -2*(angle_-25)/50; // [-1 ; 1]
                angle2 = -4*(angle_-25)/50; // [-2 ; 2]
                angle3 = -6*(angle_-25)/50; // [-3 ; 3]
                angle4 = -8*(angle_-25)/50; // [-5 ; 5] x4
                angle5 = -70-120*(angle_-25)/50; // [de 230 (=-130) à 10] x2 (120° +- 110)
            }
        }
        if (angle_ <= -18)
        {
            bouletLance_=false;
        }

        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle) // Axe
{
    qNormalizeAngle(angle);
    if (angle != zRot && !lancement_) {
        zRot = angle;

        //emit zRotationChanged(angle);

        gluDeleteQuadric(corde1);
        // corde1 = gluNewQuadric();
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{

    loadTextures();
    qglClearColor(Qt::white);
    glDisable(GL_DEPTH_TEST);
    /* glEnable( GL_BLEND );
    //glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);*/
    glEnable(GL_TEXTURE_2D);
    glDepthFunc( GL_LEQUAL );

    glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );
    //glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 4, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);


}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    double scale=abs(zoomScene_*0.1);
    qDebug()<<scale;
    glScalef(scale, scale, scale);
    glRotatef(xScene_ , 1.0, 0.0, 00);
    glRotatef(yScene_, 0.0, 1.0, 0.0);
    glRotatef(zScene_ , 0.0, 0.0, 1.0);
    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 0.0, 20.0);
#else
    glOrtho(-2, +2, -2, +2, 0.0, 20.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    /*   int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot +  dy);
        setYRotation(yRot +  dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot +  dy);
        //setZRotation(zRot +  dx);
    }

    lastPos = event->pos();*/

}

void MyGLWidget::loadTextures()
{
    QString chemin[3];

    const QString CHEMIN = ":/images";

    chemin[0]=CHEMIN+"/bois.bmp";
    chemin[1]=CHEMIN+"/pelouse.bmp";
    chemin[2]=CHEMIN+"/bois2.bmp";

    for(int i = 0;i<3;i++){
        Textures *tex=new Textures(chemin[i]);
        texture[i]=tex->getTextures();
        delete tex;
    }
}

void MyGLWidget::webcam_clicked()
{
    w->runWebCam();
}



void MyGLWidget::draw()
{
    qglColor(Qt::white);

    drawBoxBois();
    drawPelouse();
    drawLevierBois();
    drawCorde();
    drawTrebuchetComplet();

    // Debut affichage


    glPushMatrix();
    for (int colonne=-10; colonne<10; colonne++)
    {
        for (int ligne=-5; ligne<5; ligne++)
        {
            glPushMatrix();
            glTranslatef(10*ligne,10*colonne,0);
            glCallList(pelouse);
            glPopMatrix();
        }
    }

    glPushMatrix();
    glRotatef(zRot,0,0,1);
    glPushMatrix();
    glScalef(2,2,2);

    glCallList(trebuchetComplet);
    glPopMatrix();


    glDeleteLists(boxBois, 1);
    glDeleteLists(pelouse, 1);
    glDeleteLists(levierBois, 1);
    glDeleteLists(corde, 1);
    glDeleteLists(trebuchetComplet, 1);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glPopMatrix();
}

void MyGLWidget::drawBoxBois(){
    boxBois = glGenLists(1);
    glNewList(boxBois, GL_COMPILE);         // Box en bois pour constituer le trebuchet
    glPushMatrix();
    glTranslatef(-0.5, -.5, -.5);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glEnable(GL_BLEND);
    glDepthMask(GL_TRUE); // disable transparency
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
    // glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1,0,0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1,1,0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0,1,0);
    glEnd();


    glBegin(GL_QUADS);
    //    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0,0,1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1,0,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1,0,0);
    glEnd();


    glBegin(GL_QUADS);
    //  glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0,1,0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0,1,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0,0,1);
    glEnd();
    glBegin(GL_QUADS);
    //   glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,1,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1,1,0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1,1,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0,1,1);
    glEnd();
    glBegin(GL_QUADS);
    // glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1,0,1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1,1,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1,1,0);
    glEnd();
    glBegin(GL_QUADS);
    //  glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1,0,1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0,0,1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0,1,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1,1,1);
    glEnd();
    glPopMatrix();

    glDepthMask(GL_FALSE); // enable transparency
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glEndList();
}
void MyGLWidget::drawPelouse(){
    qglColor(Qt::white);
    pelouse = glGenLists(1);
    glNewList(pelouse, GL_COMPILE);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(10,0,0);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(10,10,0);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(0,10,0);

    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glEndList();
}

void MyGLWidget::drawLevierBois(){
    levierBois = glGenLists(1);
    glNewList(levierBois, GL_COMPILE);          // Levier du trébuchet
    glPushMatrix();
    glTranslatef(-0.5, -.5, -.5);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glEnable(GL_BLEND);

    glBegin(GL_QUADS);
    // glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1,0,0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1,1,0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0,1,0);
    glEnd();


    glBegin(GL_QUADS);
    //    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0,0,1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1,0,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1,0,0);
    glEnd();


    glBegin(GL_QUADS);
    //  glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0,1,0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0,1,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0,0,1);
    glEnd();
    glBegin(GL_QUADS);
    //   glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0,1,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1,1,0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1,1,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0,1,1);
    glEnd();
    glBegin(GL_QUADS);
    // glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1,0,0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1,0,1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1,1,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1,1,0);
    glEnd();
    glBegin(GL_QUADS);
    //  glNormal3f(0,0,-1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1,0,1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0,0,1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0,1,1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1,1,1);
    glEnd();
    glPopMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glEndList();
}

void MyGLWidget::drawCorde(){
    corde = glGenLists(1);
    glNewList(corde, GL_COMPILE);


    gluDeleteQuadric(corde1);
    corde1 = gluNewQuadric();

    glColor4f (1, 1, 1, 0.8);
    glPushMatrix();

    glRotatef( 90, 0, 1, 0);
    glTranslatef(0, 0, -0.5);
    glRotatef( -90, 1, 0, 0);

    glScalef( 0.2, 0.2, 0.4);
    gluCylinder(corde1, 1, 1, 1, 30, 30);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle5, 1, 0, 0);
    // glRotatef( -9, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle5, 1, 0, 0);
    // glRotatef( -9, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle4, 1, 0, 0);
    // glRotatef( -7, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle4, 1, 0, 0);
    // glRotatef( -7, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle4, 1, 0, 0);
    // glRotatef( -7, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle4, 1, 0, 0);

    // glRotatef( -5, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle3, 1, 0, 0);
    // glRotatef( -5, 1, 0 ,0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle3, 1, 0, 0);
    // glRotatef( -5, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle3, 1, 0, 0);
    // glRotatef( -5, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle3, 1, 0, 0);
    // glRotatef( -5, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle1, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle1, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( 0, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( 0, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( 0, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( 0, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 30, 30);

    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 30, 30);

    glColor4f (.75, .55, .34, 0.8);
    glScalef( 1, 1, 0.5);

    glPushMatrix();
    glTranslatef( .5, 0, 2);
    glRotatef( 35, 0, 1, 0);
    glScalef( 1, 1, 10);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glScalef( 1, 1, 0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-.5, 0, 2);
    glRotatef( -35, 0, 1, 0);
    glScalef( 1, 1, 10);
    gluCylinder(corde1, 1, 1, 1, 30, 30);
    glScalef( 1, 1, 0.1);
    glPopMatrix();

    if (!bouletLance_)
    {

        glPushMatrix();
        glTranslatef(0, 0, 2);
        glScalef( 1, 1, 10);
        gluCylinder(corde1, 1, 1, 1, 30, 30);
        glScalef( 1, 1, 0.1);
        glPopMatrix();
    }

    glPopMatrix();

    glEndList();
    // Fin corde
}

void MyGLWidget::drawTrebuchetComplet(){

    trebuchetComplet = glGenLists(1);        // Ensemble du trébuchet


    glNewList(trebuchetComplet, GL_COMPILE);
    //  glTranslatef(1,1,0.05);
    // socle
    glScalef(0.5,1,0.05);
    glCallList(boxBois);
    glPushMatrix();
    glScalef(2,1,20);
    // pieds
    glPushMatrix();
    glTranslatef( .22, -0.23, .43);
    glRotatef( 62, 1, 0, 0);
    glScalef( 0.05 ,1 ,.05);
    glCallList(boxBois);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( .22, 0.23, .43);
    glRotatef( -62, 1, 0, 0);
    glScalef( 0.05 ,1 ,.05);
    glCallList(boxBois);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -.22, -0.23, .43);
    glRotatef( 62, 1, 0, 0);
    glScalef( 0.05 ,1 ,.05);
    glCallList(boxBois);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -.22, 0.23, .43);
    glRotatef( -62, 1, 0, 0);
    glScalef( 0.05 ,1 ,.05);
    glCallList(boxBois);
    glPopMatrix();

    // bascule
    glPushMatrix ();
    glTranslatef(0,0,0.85);
    glRotatef(90,0,1,0);
    glScalef(0.02,0.02,0.5);
    glCallList(levierBois);
    // levier
    glPushMatrix ();
    glScalef(5,5,0.2);
    glRotatef(yRot,0,0,1);
    glPushMatrix ();
    glTranslatef(0,4,0);
    glScalef(1,20,1);
    //glColor3f(0,0,0);
    glCallList(levierBois);
    glPopMatrix();

    // corde

    glPushMatrix ();
    glTranslatef(.5, 13.5, 0);
    glCallList(corde);
    glPopMatrix();

    glPopMatrix ();
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glEndList();
}



