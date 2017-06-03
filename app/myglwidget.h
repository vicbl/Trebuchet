// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <GL/glu.h>
#include <QTime>
#include "grid.h"
#include "trebuchet.h"
#include "cible.h"
#include "webcam.h"
#include "game.h"
#include "boulet.h"
#include "logotelecom.h"
#include "trajectory.h"
#include "pelouse.h"
#include "save.h"
#include"lighting.h"

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
    void calculScores();
    void recentrer();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    //void keyPressEvent ( QKeyEvent * event );
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);


public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setForce(int angle);
    void lancerBoutonClicked();
    void webcam_clicked();

    void startButton_clicked();
    void setValue();
    void vueChanged();
    void trajectoryActived();
    void nightModeActived();

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

    void on_jouer_clicked(int);
    void forceChanged(int angle);
    void chrono1Refresh(QString tpPartie);
    void chrono2Refresh(QString tpTotal);
    void setName(QString name);
    void setDifficulty(QString difficulty);
    void setScore(QString score);
    void setBestPlayer(QString bestPlayer);
    void setNbCibles(QString nbCibles);



private:
    void draw();
    // void loadTextures();
    void reInitialize();

    void nightMode();
    void drawCorde();


    //Coordonnées de la scène globale
    int xScene_=80;
    int yScene_=0;
    int zScene_=180;
    int zoomScene_=2;

    int xRot_;
    int yRot;   // angle du levier
    int zRot;

    int force;
    Webcam *w;

    int xBoulet;
    int yBoulet;

    QTime tempsPartie_;
    QTime tempsTotal_;
    int angle_;

    double angle1;
    double angle2;
    double angle3;
    double angle4;
    double angle5;


    GLuint corde;
    GLuint texturePierre_;


    Pelouse * pelouse_;
    Cible * cible_;
    Boulet* boulet_;
    LogoTelecom * logoTelecom_;
    Trebuchet *trebuchet_;
    Grid *grid_;
    Trajectory *traj_;
    Lighting *light_;

    GLUquadric* corde1;

    //Light
    float posLight0[4] = {-3.3f, -1.0f, 12.5f,1.0f};
    float dirLight0[4] = {0.0f, 0.4f,-1.0f};
    float posLight1[4] = {3.3f, -1.0f, 12.5f,1.0f};
    float dirLight1[4] = {0.0f, 0.4f,-1.0f};
    float posLight2[4] = {-21.0f, 24.0f, 12.5f,1.0f};
    float dirLight2[4] = {0.5f, 0.5f,-1.0f};
    float posLight3[4] = {21.0f, 24.0f, 12.5f,1.0f};
    float dirLight3[4] = {-0.5f, 0.5f,-1.0f};


    boolean bouletLance_;
    boolean lancement_;
    boolean finCourseCorde_;
    boolean vueSuivie_=true;
    boolean trajectory_=false;
    boolean nightMode_=false;
    QPoint lastPos;

    //Variable of the game
    Game *game_;
    int difficulty_=1;
    QString name_;
    bool start_=false;
    int distanceTrebuchet_;
    int posXCible_;
    int posYCible_;
    int nbTotalCible_=0;

    Save *save_;
};

#endif // MYGLWIDGET_H
