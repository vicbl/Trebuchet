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
#include "newgamedialog.h"

#include"textures.h"
#define PI 3.14159265
using namespace std;

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

    xRot = 180; // angle de vue
    yRot = -20; // angle du levier
    zRot = 180; // axe du trébuchet
    force = -20;

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
    finCourseCorde_=false;
    vueSuivie_=true;

    // corde1 = gluNewQuadric();

    grid_= new Grid(25,75,0.01);
    trebuchet_=new Trebuchet();
    cible_=new Cible();
    boulet_=new Boulet ();
    logoTelecom_=new LogoTelecom();


    LOGOTELECOM =logoTelecom_->draw();
}

MyGLWidget::~MyGLWidget()
{
}
void MyGLWidget::setValue()
{
    if (w->getActive()){
        zRot=w->getxPosition();
        yRot=w->getyPosition();
        //qDebug()<<"x="<<zRot<<" y ="<<yRot;


        updateGL();
    }
    chrono1Refresh(QString(tempsPartie_.elapsed()));
    chrono2Refresh(QString(tempsTotal_.elapsed()));
}



// Fonction de 'sleep' : qSleep() appartient au module QtTest
static void delay(int tp)
{
    QTime dieTime= QTime::currentTime().addMSecs(tp); // Attend tp ms
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MyGLWidget::vueChanged()
{
    vueSuivie_=!vueSuivie_;
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

        delay(6);
    }
    force = -20;
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

        //int final_xRot;       // xRot final pour être derrière le trébuchet
        int angle = xRot;       // Angle de rotation du trébuchet
        boulet_->reset();
        float v0 = float(30+force)/8;
        boulet_->set_v0(v0);   // V0 du boulet, force = [-20 / -10], v0 = [.33 / 2], coord_x_final = [29 - 80]
        boulet_->set_axe(zRot);
        qDebug() << "Force = " << force << " v0 = " << v0;
        int pos_treb = 0;       // position trigonométrique du levier autour de son axe de rotation

        /*
         * zRot = angle = [100 - 180 - 260]
         * xRot = zone  = [ 0  - 180 - 360]
        */

        // ORIENTATION DE LA CAMERA
        /*
        final_xRot = 360-zRot;

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
                zScene_=angle;
                emit xRotationChanged(angle);
                gluDeleteQuadric(corde1);
                // corde1 = gluNewQuadric();
                updateGL();
            }
            // qDebug(" - %d", angle);
            delay(15);
        }

*/
        // FIN ORIENTATION DE LA CAMERA

        delay(400);

        // LANCEMENT

        bool aller = true;
        while (pos_treb<420)
        {
            if (pos_treb<170)
            {
                yRot+=3;
                if (yRot >= 110)
                {
                    bouletLance_=true;
                }

            } else if (pos_treb<265)
            {
                aller = false;
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

            if (aller)
            {
                pos_treb+=3;
            } else
            {
                pos_treb++;
            }


            angle = yRot;
            emit yRotationChanged(angle);
            gluDeleteQuadric(corde1);

            // corde1 = gluNewQuadric();
            updateGL();

           delay(6);
        }
        delay(1000);
        reInitialize();
        delay(1000);
        bouletLance_=false;

        tempsPartie_.restart();

        lancement_=false;
    }


}

void MyGLWidget::setForce(int angle)
{
    qNormalizeAngle(angle);
    if (-30-angle != yRot && !lancement_) {
        yRot = -30-angle;
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
        zScene_ = angle;
        if (angle == 361)
        {
            xRot = 1;
            zScene_=1;
        }
        if (angle == -1)
        {
            xRot = 359;
            zScene_=359;
        }
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
        // emit yRotationChanged(angle);
    }

    if (!finCourseCorde_)
    {
        angle_ = round((angle+20)*3); // angle_ va de 0 à 360, puis lacher de boulet, puis oscille entre 540 et 180 jusquà arrêt

        angle1 = 3 - round(angle_/120); // [3 ; 0] (120 = 360/3)
        angle2 = 5 - round(angle_/72); // [5 ; 0] (72 = 360/5)
        angle3 = 9 - round(angle_/40); // [9 ; 0] (40 = 360/9)
        angle4 = 14 - round(angle_/28); // [14 ; 1] (28 = 360/13)
        angle5 = 19 - round(angle_/21); // [19 ; 2] (21 = 360/17)

        if (angle_ == 510)
        {
            finCourseCorde_=true;
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
            finCourseCorde_=false;
        }


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
    qglClearColor(Qt::white);

    loadTextures();
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );
    /*glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);*/
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(-180, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 1.0,  -4.0);
    double scale=abs(zoomScene_*0.1);
    //qDebug()<<scale;
    glScalef(scale, scale, scale);
    if(bouletLance_ && vueSuivie_ && abs(360-xRot-zRot)<10)
    {
        glTranslatef(0, boulet_->get_x()/6, boulet_->get_x());
    }

    glRotatef(xScene_ , 1.0, 0.0, 00);
    glRotatef(yScene_, 0.0, 1.0, 0.0);
    glRotatef(zScene_ , 0.0, 0.0, 1.0);
    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    qDebug()<<"width "<<width<<" height "<<height;
    glViewport(0, 0, width, height);

    float aspectRatio = width / height;
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluPerspective(45.0, aspectRatio, 1.0, 1000.0);
      /* #ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 0.0, 20.0);
#else
   glOrtho(-2, +2, -2, +2, 0.0, 20.0);
    //gluOrtho2D(0.0, width, 0.0, height);
#endif*/


    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
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

void MyGLWidget::startButton_clicked()
{
    NewGameDialog dial(this);
    if (dial.exec() == QDialog::Accepted ) {
        qDebug() << "You pressed OK!";
          qDebug() <<dial.getName();
              qDebug() <<dial.getDifficulty();
    }
    qDebug()<<"start button";
}
void MyGLWidget::jouer_clicked()
{
    if (!lancement_)
    {
        CIBLE =cible_->draw();

        game_=new Game(difficulty_);
        game_->newPostion();
        start_=true;
        posXCible_=game_->getCiblePositionX();
        posYCible_=game_->getCiblePositionY();
        distanceTrebuchet_=game_->getDistanceTrebuchet();
        tempsPartie_.start();
        tempsTotal_.start();
        updateGL();
    }
}



void MyGLWidget::draw()
{
    qglColor(Qt::white);

    glClearColor(0.4f, 0.55f, 1.0f, 0.0f);

    drawCorde();
    drawPelouse();
    GLuint trebuchetComplet=trebuchet_->draw(corde,yRot);
    GLuint grid=grid_->draw();

/*
    QTime myTimer;
    myTimer.start();

    int t5 = myTimer.elapsed();
    qDebug("temps de PELOUSE' : %d", t5);
*/

    // Debut affichage

glPushMatrix();

    glPushMatrix();
    for (int colonne=-2; colonne<14; colonne++)
    {
        for (int ligne=-3; ligne<3; ligne++)
        {
            glPushMatrix();
            glTranslatef(10*ligne,10*colonne,0);
            glCallList(pelouse);
            glPopMatrix();
        }
    }
    // Draw Boulet
    if (bouletLance_)
    {
        GLuint boulet=boulet_->draw();
        glCallList(boulet);

    }

    //Draw Cible
    if (start_==true) {
        qDebug()<<"Jouer xx="<<posXCible_<<" et y="<<posYCible_;
        double angleRotationCible = atan ((posXCible_*1.0/(posYCible_*1.0+distanceTrebuchet_*1.0))) * 180 / PI;
        glPushMatrix();
        glTranslatef(0,distanceTrebuchet_,.65);
        glPushMatrix();
        glTranslatef(posXCible_,posYCible_,0);
        glScalef(1,1,1);
        glRotatef(-angleRotationCible,0,0,1);
        glCallList(CIBLE);
        glPopMatrix();
        glPopMatrix();
    }
    //End draw cible

    //*************Draw Logo***************
        glPushMatrix();
            glTranslatef(-5, -2, 1);
            glScalef(2,2,2);
            glCallList(LOGOTELECOM);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(5, -2, 1);
            glScalef(2,2,2);
            glCallList(LOGOTELECOM);
        glPopMatrix();
    //*************End Draw Logo***************

    glPushMatrix();
    glRotatef(zRot,0,0,1);
    glPushMatrix();
    glScalef(2,2,2);



    glCallList(trebuchetComplet);

    glPopMatrix();


    glPopMatrix();

    //Draw grid
    glPushMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glPushMatrix();
    glTranslatef(2,0,2);
    glRotatef(70,0,1,0);
    glScalef(0.5,0.2,0.75);
    glCallList(grid);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();

    glRotatef(90,1,0,0);
    glPushMatrix();
    glTranslatef(-2,0,2);
    glRotatef(110,0,1,0);
    glScalef(0.5,0.2,0.75);
    glCallList(grid);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    //end Draw grid


    glDeleteLists(pelouse, 1);

    glDeleteLists(corde, 1);
    glDeleteLists(trebuchetComplet, 1);

    glDeleteLists(grid, 1);



    glPopMatrix();
    glPopMatrix();


}


void MyGLWidget::drawPelouse(){
    qglColor(Qt::white);
    pelouse = glGenLists(1);

    glNewList(pelouse, GL_COMPILE);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

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


    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEndList();
}



void MyGLWidget::drawCorde(){

    corde = glGenLists(1);
    glNewList(corde, GL_COMPILE);

    xBoulet = 0;
    yBoulet = 0;


    corde1 = gluNewQuadric();

    glColor4f (1, 1, 1, 0.8);
    glPushMatrix();

    glRotatef( 90, 0, 1, 0);
    glTranslatef(0, 0, -0.5);
    glRotatef( -90, 1, 0, 0);

    glScalef( 0.2, 0.2, 0.4);
    gluCylinder(corde1, 1, 1, 1, 10, 10);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle5, 1, 0, 0);
    // glRotatef( -9, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle5, 1, 0, 0);
    // glRotatef( -9, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle4, 1, 0, 0);
    // glRotatef( -7, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle4, 1, 0, 0);
    // glRotatef( -7, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle4, 1, 0, 0);
    // glRotatef( -7, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle4, 1, 0, 0);

    // glRotatef( -5, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle3, 1, 0, 0);
    // glRotatef( -5, 1, 0 ,0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle3, 1, 0, 0);
    // glRotatef( -5, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle3, 1, 0, 0);
    // glRotatef( -5, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle3, 1, 0, 0);
    // glRotatef( -5, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle2, 1, 0, 0);
    // glRotatef( -3, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle1, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( angle1, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);

    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( 0, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( 0, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( 0, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef( 1, 1, 0.5);
    glRotatef( 0, 1, 0, 0);
    // glRotatef( -2, 1, 0, 0);
    glScalef( 1, 1, 2);
    glTranslatef(0, 0, 0.5);
    gluCylinder(corde1, 1, 1, 1, 10, 10);

    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glTranslatef(0, 0, 1);
    gluCylinder(corde1, 1, 1, 1, 10, 10);

    glColor4f (.75, .55, .34, 0.8);
    glScalef( 1, 1, 0.5);

    glPushMatrix();
    glTranslatef( .5, 0, 2);
    glRotatef( 35, 0, 1, 0);
    glScalef( 1, 1, 10);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glScalef( 1, 1, 0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-.5, 0, 2);
    glRotatef( -35, 0, 1, 0);
    glScalef( 1, 1, 10);
    gluCylinder(corde1, 1, 1, 1, 10, 10);
    glScalef( 1, 1, 0.1);
    glPopMatrix();

    if (!bouletLance_)
    {
        glTranslatef(0, 0, 12);
        glPushMatrix();
            glColor3f(.55, .55, .55);
            GLUquadric* bou = gluNewQuadric();
            gluSphere(bou, 5, 10, 10);
            gluDeleteQuadric(bou);
        glPopMatrix();

    }

    glPopMatrix();
    gluDeleteQuadric(corde1);

    glEndList();
    // Fin corde*/
}

