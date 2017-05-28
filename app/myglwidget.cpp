
// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
//#include <QKeyEvent>
#include <iostream>
#include <string>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "myglwidget.h"
#include "ui_window.h"
#include <GL/glu.h>
#include <QDebug>
#include <cmath>
#include "newgamedialog.h"
#include "save.h"

#include"textures.h"
#define PI 3.14159265
using namespace std;

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

    xRot = 180; // angle de vue
    yRot = -20; // angle du levier
    zRot = 180; // axe du trébuchet
    force = -40;

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

    pelouse_=new Pelouse();
    grid_= new Grid(25,75,0.01);
    trebuchet_=new Trebuchet();
    cible_=new Cible();
    boulet_=new Boulet ();
    logoTelecom_=new LogoTelecom();
    traj_ =new Trajectory();

save_=new Save("D:/Utilisateur/Victor/Bureau/Nouveau dossier/Nouveau dossier/files/BestScores.txt");
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::setValue()
{
    if (w->getActive()){

        /*
         * pour une webcam 640x480
         * x -> 510
         * y -> 350
         *
         * z -> 100 - 260
         * f -> -40 - 0
         *
         */

        int z = 260+int(w->getxPosition()*160.0/510);
        int f = int(w->getyPosition()*(-40.0)/350);
        bool lancer = w->getOrdreLancer();
        if(!lancer)
        {
            setZRotation(z);
            setForce(f);
            //qDebug()<<"x = "<<zRot<<" y = "<<yRot;
            updateGL();
        } else
        {
            lancerBoutonClicked();
        }
    }

    QTime t1 = QTime(0,0,0,0).addMSecs(tempsPartie_.elapsed());
    QTime t2 = QTime(0,0,0,0).addMSecs(tempsTotal_.elapsed());
    QString st1 = QString::number(t1.minute()) + ":" + QString::number(t1.second()) + "." + QString::number(round(t1.msec()/100)) ;
    QString st2 = QString::number(t2.minute()) + ":" + QString::number(t2.second()) ;

    chrono1Refresh(st1);
    chrono2Refresh(st2);

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
void MyGLWidget::trajectoryActived()
{
    trajectory_=!trajectory_;
    updateGL();
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
}

int MyGLWidget::getXScene(){return xScene_;}
int MyGLWidget::getYScene(){return yScene_;}
int MyGLWidget::getZScene(){return zScene_;}
int MyGLWidget::getZoomScene(){return zoomScene_;}
void MyGLWidget::setXScene( int x){xScene_=x;}
void MyGLWidget::setYScene( int y){yScene_=y;}
void MyGLWidget::setZScene( int z){zScene_=z;}
void MyGLWidget::setZoomScene( int zoom){zoomScene_=zoom;}

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

void MyGLWidget::recentrer()    // appeler lors de l'appui sur 'x'
{

    // ORIENTATION DE LA CAMERA
    int final_xRot;       // xRot final pour être derrière le trébuchet
    int angle = xRot;       // Angle de rotation du trébuchet

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
        delay(6);
    }

}

void MyGLWidget::lancerBoutonClicked()
{
    if (!lancement_)
    {

        // INITIALISATION

        lancement_=true;

        int angle = xRot;       // Angle de rotation du trébuchet
        boulet_->reset();
        float v0 = float(28+(float(force)/4-10))/8;
        boulet_->set_v0(v0);   // V0 du boulet, force = [-20 / -10], v0 = [1 / 2.25], coord_x_final = [29 - 99]
        boulet_->set_axe(zRot);
        qDebug() << "Force = " << force << " v0 = " << v0;
        int pos_treb = 20+yRot;       // position trigonométrique du levier autour de son axe de rotation

        /*
         * zRot = angle = [100 - 180 - 260]
         * xRot = zone  = [ 0  - 180 - 360]
        */

        // FIN ORIENTATION DE LA CAMERA

        delay(400);

        // LANCEMENT

        bool aller = true;
        while (pos_treb<420)
                {
                    if (pos_treb<172)
                    {
                        yRot+=3;
                        if (yRot >= 110)
                        {
                            bouletLance_=true;
                        }

                    } else if (pos_treb<266)
                    {
                        aller = false;
                        yRot-=2;
                    } else if (pos_treb<324)
                    {
                        yRot+=2;
                    } else if (pos_treb<370)
                    {
                        yRot-=2;
                    } else if (pos_treb<400)
                    {
                        yRot+=2;
                    } else if (pos_treb<416)
                    {
                        yRot-=2;
                    }else
                    {
                        yRot+=2;
                    }

                    if (aller)
                    {
                        pos_treb+=3;
                    } else
                    {
                        pos_treb+=2;
                    }


                    angle = yRot;
                    emit yRotationChanged(angle);
                    gluDeleteQuadric(corde1);

                    updateGL();

                   delay(6);
                }

        delay(1000);
        reInitialize();
        delay(1000);
        bouletLance_=false;

        tempsPartie_.restart();

        lancement_=false;
        w->setOrdreLancer(lancement_);

        // si la partie a commencée permet de calculé les scores
        if (start_){
            calculScores();
        }

    }


}

void MyGLWidget::setForce(int angle)
{
    delay(6);
    qNormalizeAngle(angle);
    if (angle/2 != yRot && !lancement_) {
        yRot = angle/2;
        force = angle;
        emit yRotationChanged(angle/2);
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
    delay(6);
    qNormalizeAngle(angle);
    if (angle != zRot && !lancement_) {
        zRot = angle;

        emit zRotationChanged(angle);

        updateGL();
    }
}

void MyGLWidget::initializeGL()
{


    logoTelecom_->draw();
    grid_->draw();
    cible_->draw();
    pelouse_->draw();
 texturePierre_=((Textures(":/images/pierre.bmp")).getTextures());
    qglClearColor(Qt::white);


    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    //static GLfloat lightPosition[4] = { 0, 0, 1, 0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
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


void MyGLWidget::webcam_clicked()
{
    w->runWebCam();
}

void MyGLWidget::startButton_clicked()
{
    NewGameDialog newGame(this);


    if (newGame.exec() == QDialog::Accepted )
    {
        nbTotalCible_=0;
        difficulty_=newGame.getDifficulty();
        name_=newGame.getName();
        game_=new Game(difficulty_,name_);
        game_->newPostion();
        start_=true;
        posXCible_=game_->getCiblePositionX();
        posYCible_=game_->getCiblePositionY();
        distanceTrebuchet_=game_->getDistanceTrebuchet();
        tempsPartie_.start();
        tempsTotal_.start();
        setName(name_);
        if (save_->getBest(difficulty_)!=""){
            setBestPlayer(save_->getBest(difficulty_));
        }
        setDifficulty( QString::number(difficulty_));
        updateGL();
    }
    qDebug()<<"start button";
}

void MyGLWidget::calculScores(){
    if(nbTotalCible_<5){
        game_->calculScore(boulet_->get_x(),zRot);
        //qDebug()<<"fin";

        if(game_->getCibleTouchee()){
            game_->newPostion();
            yBoulet=true;
            // nouvelle cible
            posXCible_=game_->getCiblePositionX();
            posYCible_=game_->getCiblePositionY();
            distanceTrebuchet_=game_->getDistanceTrebuchet();
            tempsPartie_.start();
            setNbCibles(QString::number(game_->getNbTotalCibleTouchee()));
        }

        nbTotalCible_++;
        setScore( QString::number(game_->getScore())+" / "+ QString::number(nbTotalCible_));
        zRot = 180; // axe du trébuchet
        force = -40;
        yRot = -20;
        emit zRotationChanged(zRot);
        emit yRotationChanged(yRot);
        emit forceChanged(force);
        updateGL();

    }
    if (nbTotalCible_==5){
        qDebug()<<"Partie terminée";
        QString message="Vous avez marqué "+QString::number(game_->getScore())+" / "+QString::number(nbTotalCible_)+" points pour la difficulté "+QString::number(difficulty_);
        QMessageBox::information(this,tr("Fin de partie"),message);

        save_->saveBest(game_->getScore(),difficulty_,name_);

        // On réinitialise les valeur et l'affichage
        setScore( QString::number(0));
        setNbCibles(QString::number(0));
        setBestPlayer("Pas de meilleur score");
        setDifficulty( QString::number(0));
        start_=false;
        zRot = 180; // axe du trébuchet
        force = -40;
        yRot = -20; // angle levier
        emit zRotationChanged(zRot);
        emit yRotationChanged(yRot);
        emit forceChanged(force);
        updateGL();
    }

}


void MyGLWidget::draw()
{

    qglColor(Qt::white);

    glClearColor(0.4f, 0.55f, 1.0f, 0.0f);

    drawCorde();




    /*
    QTime myTimer;
    myTimer.start();
    int t5 = myTimer.elapsed();
    qDebug("temps de PELOUSE' : %d", t5);
*/





    // Debut affichage
    glPushMatrix();

    //************** Draw Gazon ****************
    for (int colonne=-2; colonne<14; colonne++)
    {
        for (int ligne=-3; ligne<3; ligne++)
        {
            glPushMatrix();
                glTranslatef(10*ligne,10*colonne,0);
                glCallList(pelouse_->getPelouse());
            glPopMatrix();
        }
    }
    //************** End Draw Gazon *************


    //************** Draw Trajectory ****************
    if (trajectory_)
    {
        float v0 = float(28+(float(force)/4-10))/8;
        traj_->set_v0(v0);   // V0 du boulet, force = [-20 / -10], v0 = [1 / 2.25], coord_x_final = [29 - 99]
        traj_->set_axe(zRot);
        glCallList(traj_->draw());
    }
    //************** End Draw Trajectory *************





    //************** Draw Boulet ****************
    if (bouletLance_)
    {
        GLuint boulet=boulet_->draw();
        glCallList(boulet);
    }
    //************ End Draw Boulet ***************


    //********** Draw Cible ***************
    if (start_==true) {
        //qDebug()<<"Jouer xx="<<posXCible_<<" et y="<<posYCible_;
        double angleRotationCible = atan ((posXCible_*1.0/(posYCible_*1.0+distanceTrebuchet_*1.0))) * 180 / PI;
        glPushMatrix();
            glTranslatef(0,distanceTrebuchet_,.65);
            glPushMatrix();
                glTranslatef(posXCible_,posYCible_,0);
                glRotatef(-angleRotationCible,0,0,1);
                glScalef(1,1,1);
                glCallList(cible_->getCompleteCible());
            glPopMatrix();
        glPopMatrix();
    }
    //*********** End draw cible **********

    //*************Draw Logo***************
        glPushMatrix();
            glTranslatef(-5, -2, 1);
            glScalef(2,2,2);
            glCallList(logoTelecom_->getCompleteLogoTelecom());
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-7.6, 0, 1);
            glRotatef(-60, 0,0,1);
            glScalef(2,2,2);
            glCallList(logoTelecom_->getCompleteLogoTelecom());
        glPopMatrix();
        glPushMatrix();
            glTranslatef(5, -2, 1);
            glScalef(2,2,2);
            glCallList(logoTelecom_->getCompleteLogoTelecom());
        glPopMatrix();
        glPushMatrix();
            glTranslatef(7.6, 0, 1);
            glRotatef(60, 0,0,1);
            glScalef(2,2,2);
            glCallList(logoTelecom_->getCompleteLogoTelecom());
        glPopMatrix();
    //*************End Draw Logo***************


    //************* Draw TREBUCHET ***************
    glPushMatrix();
        glRotatef(zRot,0,0,1);
        glPushMatrix();
            glScalef(2,2,2);
            glCallList(trebuchet_->draw(corde,yRot));
        glPopMatrix();
    glPopMatrix();

    //************* End Draw TREBUCHET ***************

    //**************** Draw grid *********************
    glPushMatrix();

        glPushMatrix();
            glRotatef(90,1,0,0);
            glPushMatrix();
                glTranslatef(2,0,2);
                glRotatef(60,0,1,0);
                glScalef(0.6,0.25,.5);
                glCallList(grid_->getCompleteGrid());
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glRotatef(90,1,0,0);
            glPushMatrix();
                glTranslatef(-2,0,2);
                glRotatef(120,0,1,0);
                glScalef(0.6,0.25,0.5);
                glCallList(grid_->getCompleteGrid());
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    //*************** End Draw grid *********************



    glDeleteLists(corde, 100);
   // glDeleteLists(trebuchetComplet, 1);

    glPopMatrix();

glFlush();
}



void MyGLWidget::drawCorde(){

    corde = glGenLists(1);
    glNewList(corde, GL_COMPILE);
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
            glColor3f(1, 1, 1);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturePierre_);
                GLUquadric* bou = gluNewQuadric();
                gluQuadricTexture(bou,GL_TRUE);
                gluSphere(bou, 5, 10, 10);
                glDisable(GL_TEXTURE_2D);
                gluDeleteQuadric(bou);
            glPopMatrix();

        }

    glPopMatrix();
    gluDeleteQuadric(corde1);

    glEndList();
    // Fin corde*/
}

