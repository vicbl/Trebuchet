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
    bool getStarted(){return start_;}

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    //void keyPressEvent ( QKeyEvent * event );
    QSize minimumSizeHint() const;
    QSize sizeHint() const;


public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setForce(int angle);
    void lancerBoutonClicked();


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
    void setNbCibles(QString nbCibles);

//Meilleurs scores
    void setBestName1(QString);
    void setBestName2(QString);
    void setBestName3(QString);
    void setBestName4(QString);
    void setBestName5(QString);

    void setBestScore1(QString);
    void setBestScore2(QString);
    void setBestScore3(QString);
    void setBestScore4(QString);
    void setBestScore5(QString);

    void disableButton(bool);
private:
    void draw();
    // void loadTextures();
    void reInitialize();

    void nightMode();
    void drawCorde();

    void setBestScores();


    //Coordonnées de la scène globale
    int xScene_=80;
    int yScene_=0;
    int zScene_=180;
    int zoomScene_=2;

    int xRot_;
    int yRot_;   // angle du levier
    int zRot_;

    int force_;
    Webcam *w_;

    int xBoulet_;
    int yBoulet_;

    QTime tempsPartie_;
    QTime tempsTotal_;
    int angle_;

    double angle1_;
    double angle2_;
    double angle3_;
    double angle4_;
    double angle5_;


    GLuint corde_;
    GLuint texturePierre_;


    Pelouse * pelouse_;
    Cible * cible_;
    Boulet* boulet_;
    LogoTelecom * logoTelecom_;
    Trebuchet *trebuchet_;
    Grid *grid_;
    Trajectory *traj_;
    Lighting *light_;

    GLUquadric* corde1_;

    //Light
    float posLight0_[4] = {-3.3f, -1.0f, 12.5f,1.0f};
    float dirLight0_[4] = {0.0f, 0.4f,-1.0f};
    float posLight1_[4] = {3.3f, -1.0f, 12.5f,1.0f};
    float dirLight1_[4] = {0.0f, 0.4f,-1.0f};
    float posLight2_[4] = {-21.0f, 24.0f, 12.5f,1.0f};
    float dirLight2_[4] = {0.5f, 0.5f,-1.0f};
    float posLight3_[4] = {21.0f, 24.0f, 12.5f,1.0f};
    float dirLight3_[4] = {-0.5f, 0.5f,-1.0f};


    boolean bouletLance_;
    boolean lancement_;
    boolean finCourseCorde_;
    boolean vueSuivie_=true;
    boolean trajectory_=false;
    boolean nightMode_=false;
    QPoint lastPos_;

    //Variable du jeu
    Game *game_;
    int difficulty_=1;
    QString name_;
    bool start_=false;
    int distanceTrebuchet_;
    int posXCible_;
    int posYCible_;
    int nbTotalCible_=5;
    int nbCibleTouchee_=0;
    int nbCiblePassee_=0;
    int compteurEssai_=0;
    Save *save_;
};

#endif // MYGLWIDGET_H
