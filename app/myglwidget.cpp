
// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
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

    xRot_ = 180; // angle de vue
    yRot_ = 0; // angle du levier
    zRot_ = 180; // axe du trébuchet
    force_ = -40;

    angle_ = 0;
    angle1_ = 3;
    angle2_ = 5;
    angle3_ = 9;
    angle4_ = 14;
    angle5_ = 19;

    w_=new Webcam();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(setValue()));
    timer->start(10);

    bouletLance_ = false;
    lancement_ = false;
    finCourseCorde_=false;
    vueSuivie_=true;
    // corde1 = gluNewQuadric();

    light_=new Lighting();
    pelouse_=new Pelouse();
    grid_= new Grid(25,75,0.01);
    trebuchet_=new Trebuchet();
    cible_=new Cible();
    boulet_=new Boulet ();
    logoTelecom_=new LogoTelecom();
    traj_ =new Trajectory();
    QDir dir;
    qDebug() << "chemin"<<dir.absolutePath();
    dir.mkdir("Sauvegardes");
    QString path=dir.absolutePath()+"/Sauvegardes/BestScores.txt";
    qDebug()<<path;
    save_=new Save(path);


    //On met a jour le classemnt des meilleur score
    setBestScores();
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::setValue()
{
    if (w_->getActive()){

        /*
         * pour une webcam 640x480
         * x -> 510
         * y -> 350
         *
         * z -> 100 - 260
         * f -> -40 - 0
         *
         */

        int z = 260-int(w_->getxPosition()*160.0/510);
        int f = int(w_->getyPosition()*(-40.0)/350);
        bool lancer = w_->getOrdreLancer();
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
    QString st1 ="0:0.0" ;
    QString st2 ="0:0"  ;
    if(start_){
        st1 = QString::number(t1.minute()) + ":" + QString::number(t1.second()) + "." + QString::number(round(t1.msec()/100)) ;
        st2 = QString::number(t2.minute()) + ":" + QString::number(t2.second()) ;
    }
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
    while (yRot_>-20)
    {
        yRot_--;
        int angle = yRot_;
        emit yRotationChanged(angle);
        gluDeleteQuadric(corde1_);
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
    int angle = xRot_;       // Angle de rotation du trébuchet

    final_xRot = 360-zRot_;
    //qDebug(" - %d - %d", final_xRot, angle);
    while(final_xRot!=angle)
    {
        if (xRot_<final_xRot)
        {
            angle++;
        } else
        {
            angle--;
        }
        qNormalizeAngle(angle);
        if (angle != xRot_)
        {
            xRot_ = angle;
            zScene_=angle;
            emit xRotationChanged(angle);
            gluDeleteQuadric(corde1_);
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

        int angle = xRot_;       // Angle de rotation du trébuchet
        boulet_->reset();
        float v0 = float(28+(float(force_)/4-10))/8;
        boulet_->set_v0(v0);   // V0 du boulet, force = [-20 / -10], v0 = [1 / 2.25], coord_x_final = [29 - 99]
        boulet_->set_axe(zRot_);
        qDebug() << "Force = " << force_ << " v0 = " << v0;
        int pos_treb = 20+yRot_;       // position trigonométrique du levier autour de son axe de rotation

        /*
         * zRot = angle = [100 - 180 - 260]
         * xRot_ = zone  = [ 0  - 180 - 360]
        */

        // FIN ORIENTATION DE LA CAMERA
        // recentrer();

        delay(400);

        // LANCEMENT

        bool aller = true;
        while (pos_treb<420)
                {
                    if (pos_treb<172)
                    {
                        yRot_+=3;
                        if (yRot_ >= 110)
                        {
                            bouletLance_=true;
                        }

                    } else if (pos_treb<266)
                    {
                        aller = false;
                        yRot_-=3;
                    } else if (pos_treb<324)
                    {
                        yRot_+=3;
                    } else if (pos_treb<370)
                    {
                        yRot_-=3;
                    } else if (pos_treb<400)
                    {
                        yRot_+=2;
                    } else if (pos_treb<416)
                    {
                        yRot_-=2;
                    }else
                    {
                        yRot_+=2;
                    }

                    if (pos_treb>=370)
                    {
                        pos_treb+=3;
                    } else
                    {
                        pos_treb+=2;
                    }


                    angle = yRot_;
                    emit yRotationChanged(angle);
                    gluDeleteQuadric(corde1_);

                    updateGL();

                   delay(6);
                }

        delay(1000);
        reInitialize();
        delay(1000);
        bouletLance_=false;
        updateGL();

        lancement_=false;
        w_->setOrdreLancer(lancement_);

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
    if (-20-angle/2 != yRot_ && !lancement_) {
        yRot_ = angle/2;
        force_ = angle;
        emit yRotationChanged(-20-angle/2);
        emit forceChanged(angle);

        gluDeleteQuadric(corde1_);
        // corde1 = gluNewQuadric();
        updateGL();
    }
}

void MyGLWidget::setXRotation(int angle) // Zone
{
    qNormalizeAngle(angle);
    if (angle != xRot_) {
        xRot_ = angle;
        zScene_ = angle;
        if (angle == 361)
        {
            xRot_ = 1;
            zScene_=1;
        }
        if (angle == -1)
        {
            xRot_ = 359;
            zScene_=359;
        }
        emit xRotationChanged(angle);

        gluDeleteQuadric(corde1_);
        // corde1 = gluNewQuadric();

        updateGL();
    }

}

void MyGLWidget::setYRotation(int angle) // bascule trébuchet
{
    qNormalizeAngle(angle);
    if (angle != yRot_) {
        yRot_ = angle;
        // emit yRotationChanged(angle);
    }

    if (!finCourseCorde_)
    {
        angle_ = round((angle+20)*3); // angle_ va de 0 à 360, puis lacher de boulet, puis oscille entre 540 et 180 jusquà arrêt

        angle1_ = 3 - round(angle_/120); // [3 ; 0] (120 = 360/3)
        angle2_ = 5 - round(angle_/72); // [5 ; 0] (72 = 360/5)
        angle3_ = 9 - round(angle_/40); // [9 ; 0] (40 = 360/9)
        angle4_ = 14 - round(angle_/28); // [14 ; 1] (28 = 360/13)
        angle5_ = 19 - round(angle_/21); // [19 ; 2] (21 = 360/17)

        if (angle_ == 510)
        {
            finCourseCorde_=true;
        }
    } else
    {
        angle_ = round(angle); // angle_ va de -20 à 160

        if (angle_ > 130)
        {
            angle1_ = -1*(angle_-145)/15; // [-1 ; 1]
            angle2_ = -2*(angle_-145)/15; // [-2 ; 2]
            angle3_ = -4*(angle_-145)/15; // [-3 ; 3]
            angle4_ = -6*(angle_-145)/15; // [-5 ; 5] x4
            angle5_ = -25+25*(angle_-145)/15;   // x2  -> de 0 à -50°
        }
        else {
            if (angle_ > 50)
            {
                angle1_ = 4*(angle_-90)/40; //
                angle2_ = 3*(angle_-90)/40; //
                angle3_ = 2*(angle_-90)/40; //
                angle4_ = 1*(angle_-90)/40; // x4
                angle5_ = -90+(angle_-90); // x2  -> de -50 à -130

            } else
            {
                angle1_ = -2*(angle_-25)/50; // [-1 ; 1]
                angle2_ = -4*(angle_-25)/50; // [-2 ; 2]
                angle3_ = -6*(angle_-25)/50; // [-3 ; 3]
                angle4_ = -8*(angle_-25)/50; // [-5 ; 5] x4
                angle5_ = -70-120*(angle_-25)/50; // [de 230 (=-130) à 10] x2 (120° +- 110)
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
    if (angle != zRot_ && !lancement_) {
        zRot_ = angle;

        emit zRotationChanged(angle);

        updateGL();
    }
}

void MyGLWidget::initializeGL()
{



    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );


    glShadeModel(GL_SMOOTH);
    Textures * tex= new Textures();

    texturePierre_=tex->getTextures(12);


    pelouse_->setTexture(*tex);
    boulet_->setTexture(*tex);
    cible_->setTexture(*tex);
    light_->setTexture(*tex);
    logoTelecom_->setTexture(*tex);
    trebuchet_->setTexture(*tex);
    grid_->setTexture(*tex);


    light_->draw();
    logoTelecom_->draw();
    grid_->draw();
    pelouse_->draw();
    cible_->draw();

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
    if(bouletLance_ && vueSuivie_ && abs(360-xRot_-zRot_)<10)
    {
        glTranslatef(0, boulet_->get_x()/6, boulet_->get_x());
    }

    glRotatef(xScene_ , 1.0, 0.0, 00);
    glRotatef(yScene_, 0.0, 1.0, 0.0);
    glRotatef(zScene_ , 0.0, 0.0, 1.0);

    //Set Lights positions
    glLightfv(GL_LIGHT0, GL_POSITION, posLight0_);
    glLightfv(GL_LIGHT1, GL_POSITION, posLight1_);
    glLightfv(GL_LIGHT2, GL_POSITION, posLight2_);
    glLightfv(GL_LIGHT3, GL_POSITION, posLight3_);
    glLightfv(GL_LIGHT4, GL_POSITION, posLight4_);
    glLightfv(GL_LIGHT5, GL_POSITION, posLight5_);
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


void MyGLWidget::setBestScores(){
    //Meilleur scores
    if (save_->getBestName(1)!=""){
        setBestName1(save_->getBestName(1));
        setBestScore1(QString::number(save_->getBestScore(1)));
    }else{
        setBestName1("Aucun");
        setBestScore1(QString::number(0));
    }
    if (save_->getBestName(2)!=""){
        setBestName2(save_->getBestName(2));
        setBestScore2(QString::number(save_->getBestScore(2)));
    }else{
        setBestName2("Aucun");
        setBestScore2(QString::number(0));
    }
    if (save_->getBestName(3)!=""){
        setBestName3(save_->getBestName(3));
        setBestScore3(QString::number(save_->getBestScore(3)));
    }else{
        setBestName3("Aucun");
        setBestScore3(QString::number(0));
    }
    if (save_->getBestName(4)!=""){
        setBestName4(save_->getBestName(4));
        setBestScore4(QString::number(save_->getBestScore(4)));
    }else{
        setBestName4("Aucun");
        setBestScore4(QString::number(0));
    }
    if (save_->getBestName(5)!=""){
        setBestName5(save_->getBestName(5));
        setBestScore5(QString::number(save_->getBestScore(5)));
    }else{
        setBestName5("Aucun");
        setBestScore5(QString::number(0));
    }
}



void MyGLWidget::startButton_clicked()
{
    NewGameDialog newGame(this);
    if (newGame.exec() == QDialog::Accepted )
    {

        nbCibleTouchee_=0;
        nbCiblePassee_=0;
        compteurEssai_=0;
        difficulty_=newGame.getDifficulty();
        name_=newGame.getName();
        game_=new Game(difficulty_);
        game_->newPostion();
        start_=true;
        posXCible_=game_->getCiblePositionX();
        posYCible_=game_->getCiblePositionY();
        distanceTrebuchet_=game_->getDistanceTrebuchet();
        tempsPartie_.start();
        tempsTotal_.start();
        setName(name_);
        setBestScores();
        emit(disableButton(start_));
        setDifficulty( QString::number(difficulty_));
        setNbCibles(QString::number(nbTotalCible_));
        updateGL();
        w_->runWebCam();

    }
    qDebug()<<"start button";
}

void MyGLWidget::calculScores(){
    if(nbCiblePassee_<nbTotalCible_){
        compteurEssai_++;
        if(compteurEssai_<3){ // Si on fait plus de 3 essai pour une cible
            if(game_->getCibleTouchee()){
                compteurEssai_=0;
                nbCiblePassee_++;
                nbCibleTouchee_++;
                game_->newPostion();
                yBoulet_=true;
                // nouvelle cible
                posXCible_=game_->getCiblePositionX();
                posYCible_=game_->getCiblePositionY();
                distanceTrebuchet_=game_->getDistanceTrebuchet();
                tempsPartie_.start();
                setNbCibles(QString::number(nbTotalCible_-nbCiblePassee_));
            }
        }else{
            nbCiblePassee_++;
            compteurEssai_=0;
            game_->newPostion();
            yBoulet_=true;
            // nouvelle cible
            posXCible_=game_->getCiblePositionX();
            posYCible_=game_->getCiblePositionY();
            distanceTrebuchet_=game_->getDistanceTrebuchet();
            tempsPartie_.start();
            setNbCibles(QString::number(nbTotalCible_-nbCiblePassee_));
        }
        setScore( QString::number(game_->getScore()));
        zRot_ = 180; // axe du trébuchet
        force_ = -40;
        yRot_ = 0;
        emit zRotationChanged(zRot_);
        emit yRotationChanged(yRot_);
        emit forceChanged(force_);
        updateGL();
    }

    //Si la partie est finie
    if (nbCiblePassee_==nbTotalCible_){
        qDebug()<<"Partie terminée";
        int meilleurScore=save_->getBestScore(difficulty_);
        save_->saveBest(game_->getScore(),difficulty_,name_);
        QString message;
        if(meilleurScore> game_->getScore() && save_->getBestName(difficulty_)!="" ){
             message="Vous avez touché "+QString::number(nbCibleTouchee_)+ " cibles sur "
                    +QString::number(nbTotalCible_)+" et marqué "+QString::number(game_->getScore())+
                    " points pour la difficulté "+QString::number(difficulty_)+".\n"+
                    "Le meilleur score est détenu par "+save_->getBestName(difficulty_)+" avec "+
                    QString::number(save_->getBestScore(difficulty_))+" points.";
        }else{
             message="Vous avez touché "+QString::number(nbCibleTouchee_)+ " cibles  sur "
                    +QString::number(nbTotalCible_)+" et marqué "+QString::number(game_->getScore())+
                    " points pour la difficulté "+QString::number(difficulty_)+".\n"+
                    "Bravo vous avez fait le meilleur score !";
        }
        QMessageBox::information(this,tr("Fin de partie"),message);



        // On réinitialise les valeur et l'affichage
        setScore( QString::number(0));
        setNbCibles(QString::number(0));
        setBestScores();
        setName("Name");
        setDifficulty( QString::number(0));
        setNbCibles(QString::number(0));
        start_=false;
        zRot_ = 180; // axe du trébuchet
        force_ = -40;
        yRot_ = 0; // angle levier
        emit zRotationChanged(zRot_);
        emit yRotationChanged(yRot_);
        emit forceChanged(force_);
        emit disableButton(start_);
        updateGL();
        w_->setOrdreFermer(true);
    }

}

void MyGLWidget::nightMode(){
    GLfloat ambient[] = { 50.0, 50.0f, 50.0f, 50.0f };

    //Configure light 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,2.5);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,0.8);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,0.2);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,50.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dirLight0_);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT,2.0);


    //Configure light 1
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,2.5);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION,0.8);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION,0.2);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,50.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dirLight1_);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,2.0);

    //Configure light 2
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION,2.5);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION,0.8);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION,0.2);

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF,80.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dirLight2_);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT,2.0);

    //Configure light 3
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION,2.5);
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION,0.8);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION,0.2);

    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF,80.0);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dirLight3_);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT,2.0);

    //Configure light 4
    glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
    glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION,2.5);
    glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION,0.8);
    glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION,0.2);

    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF,80.0);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dirLight4_);
    glLightf(GL_LIGHT4, GL_SPOT_EXPONENT,2.0);

    //Configure light 5
    glLightfv(GL_LIGHT5, GL_AMBIENT, ambient);
    glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION,2.5);
    glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION,0.8);
    glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION,0.2);

    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF,80.0);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dirLight5_);
    glLightf(GL_LIGHT5, GL_SPOT_EXPONENT,2.0);


    //Enable all lights
    glEnable(GL_LIGHTING);
    glEnable((GL_LIGHT0));
    glEnable((GL_LIGHT1));
    glEnable((GL_LIGHT2));
    glEnable((GL_LIGHT3));
    glEnable((GL_LIGHT4));
    glEnable((GL_LIGHT5));
}

void MyGLWidget::nightModeActived(){
    nightMode_=!nightMode_;
    updateGL();
}

void MyGLWidget::draw()
{

    qglColor(Qt::white);

    glClearColor(0.4f, 0.55f, 1.0f, 0.0f);

    /*
    QTime myTimer;
    myTimer.start();
    int t5 = myTimer.elapsed();
    qDebug("temps de PELOUSE' : %d", t5);
*/

    if (nightMode_){
        nightMode();
    }else{

        glDisable((GL_LIGHTING));
        glDisable((GL_LIGHT0));
        glDisable((GL_LIGHT1));
        glDisable((GL_LIGHT2));
        glDisable((GL_LIGHT3));
    }


    drawCorde();

    // Debut affichage
    glPushMatrix();
          //************** Draw Gazon ****************
         glPushMatrix();
             for (int colonne=-2; colonne<14; colonne++)
            {
                for (int ligne=-4; ligne<4; ligne++)
                {
                    glPushMatrix();
                        glTranslatef(10*ligne,10*colonne,0);
                        glCallList(pelouse_->getPelouse());
                    glPopMatrix();
                }
            }
        glPopMatrix();
        //************** End Draw Gazon *************

        //************** Draw Trajectory ****************
        if (trajectory_)
        {
            float v0 = float(28+(float(force_)/4-10))/8;
            traj_->set_v0(v0);   // V0 du boulet, force = [-20 / -10], v0 = [1 / 2.25], coord_x_final = [29 - 99]
            traj_->set_axe(zRot_);
            glCallList(traj_->draw());
        }
        //************** End Draw Trajectory *************



        //************** Draw Boulet ****************
        if (bouletLance_&&start_)
        {
            GLuint boulet=boulet_->draw(game_);
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
                   // glScalef(1,1,1);
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
            glRotatef(zRot_,0,0,1);
            glPushMatrix();
                glTranslatef(0, 0, 0.2);
                glScalef(3,3,3);
                glCallList(trebuchet_->draw(corde_,yRot_));
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


        //*************** Draw Projectors *********************
        glPushMatrix();
            glColor3f(1,1,1);
            glTranslatef(5,-1,0);
            glRotatef(45,0,0,1);
            glCallList(light_->getCompleteLighting());
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-5,-1,0);
            glRotatef(-45,0,0,1);
            glCallList(light_->getCompleteLighting());
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,25,0);
            glRotatef(-45,0,0,1);
            glCallList(light_->getCompleteLighting());
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20,25,0);
            glRotatef(45,0,0,1);
            glCallList(light_->getCompleteLighting());
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-30,65,0);
            glRotatef(-45,0,0,1);
            glCallList(light_->getCompleteLighting());
        glPopMatrix();
        glPushMatrix();
            glTranslatef(30,65,0);
            glRotatef(45,0,0,1);
            glCallList(light_->getCompleteLighting());
        glPopMatrix();
        //*************** End Draw projectors *********************


        // glDeleteLists(trebuchetComplet, 1);

    glPopMatrix();
glDeleteLists(corde_, 100);
//glFlush();
}



void MyGLWidget::drawCorde(){

    corde_ = glGenLists(1);
    glNewList(corde_, GL_COMPILE);
    corde1_ = gluNewQuadric();
    gluQuadricTexture(corde1_,GL_TRUE);
    glColor4f (1, 1, 1, 0.8);
    glPushMatrix();

        glRotatef( 90, 0, 1, 0);
        glTranslatef(0, 0, -0.5);
        glRotatef( -90, 1, 0, 0);
        glScalef( 0.2, 0.2, 0.4);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);

        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle5_, 1, 0, 0);
        // glRotatef( -9, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle5_, 1, 0, 0);
        // glRotatef( -9, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);

        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle4_, 1, 0, 0);
        // glRotatef( -7, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle4_, 1, 0, 0);
        // glRotatef( -7, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle4_, 1, 0, 0);
        // glRotatef( -7, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle4_, 1, 0, 0);

        // glRotatef( -5, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle3_, 1, 0, 0);
        // glRotatef( -5, 1, 0 ,0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle3_, 1, 0, 0);
        // glRotatef( -5, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle3_, 1, 0, 0);
        // glRotatef( -5, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle3_, 1, 0, 0);
        // glRotatef( -5, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);

        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle2_, 1, 0, 0);
        // glRotatef( -3, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle2_, 1, 0, 0);
        // glRotatef( -3, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle2_, 1, 0, 0);
        // glRotatef( -3, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle2_, 1, 0, 0);
        // glRotatef( -3, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle2_, 1, 0, 0);
        // glRotatef( -3, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);

        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle1_, 1, 0, 0);
        // glRotatef( -2, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( angle1_, 1, 0, 0);
        // glRotatef( -2, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);

        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( 0, 1, 0, 0);
        // glRotatef( -2, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( 0, 1, 0, 0);
        // glRotatef( -2, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( 0, 1, 0, 0);
        // glRotatef( -2, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 0.5);
        glScalef( 1, 1, 0.5);
        glRotatef( 0, 1, 0, 0);
        // glRotatef( -2, 1, 0, 0);
        glScalef( 1, 1, 2);
        glTranslatef(0, 0, 0.5);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);

        glTranslatef(0, 0, 1);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 1);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 1);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 1);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 1);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 1);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 1);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);
        glTranslatef(0, 0, 1);
        gluCylinder(corde1_, 1, 1, 1, 10, 10);

        glColor4f (.75, .55, .34, 0.8);
        glScalef( 1, 1, 0.5);

        glPushMatrix();
            glTranslatef( .5, 0, 2);
            glRotatef( 35, 0, 1, 0);
            glScalef( 1, 1, 10);
            gluCylinder(corde1_, 1, 1, 1, 10, 10);
            glScalef( 1, 1, 0.1);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-.5, 0, 2);
            glRotatef( -35, 0, 1, 0);
            glScalef( 1, 1, 10);
            gluCylinder(corde1_, 1, 1, 1, 10, 10);
            glScalef( 1, 1, 0.1);

        glPopMatrix();
       // gluDeleteQuadric(corde1);
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


    glEndList();
    // Fin corde*/
}

