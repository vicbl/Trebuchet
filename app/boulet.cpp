#include "boulet.h"
#include <QOpenGLTexture>

#include <QtOpenGL/qgl.h>
#include <QDebug>
#include "game.h"

#define PI 3.14159265
Boulet::Boulet()
{

}

float Boulet::get_x() {return (float)coordX_;}  // Boulet entre 33 et 102
float Boulet::get_y() {return (float)coordY_;}

void Boulet::set_y(float y){coordY_=y;}
void Boulet::set_x(float x){coordX_=x;}

bool Boulet::getFin(){return finTrajectoire_;}

void Boulet::set_v0(float v){v0_=v;}
void Boulet::set_axe(int a){axe_=a;}

void Boulet::setTexture(Textures tex){
    this->texturePierre_=tex.getTextures(12);
}

GLuint Boulet::draw(Game * game_, bool slowMode)
{

    // Calcul des nouvelles coordonnées
    cibleTouchee_=game_->getCibleTouchee();
    // qDebug()<<"cible toucheeeeeee"<<cibleTouchee_;
    if(!cibleTouchee_){
        float cosa = cos(PI*20/180);
        float sina = sin(PI*20/180);


        float newx = 2.4 + v0_*cosa*t_;               // x = x0 + v0*cos(a)*t
        float newy = 10.8 + v0_*sina*t_-.02*pow(t_,2);     // y = y0 + v0*sin(a)*t + 1/2*g*t²


        if(newy>0 && !finTrajectoire_ )
        {
            coordX_ = newx;
            coordY_ = newy;
            if(slowMode){
                t_=t_+0.3;
            }else{
                t_=t_+1;
            }
            if (newy<3){
                 game_->calculScore(coordX_,coordY_);
            }
        } else
        {
            finTrajectoire_ = true;
        }
    }


    // qDebug() << "Boulet : " << coordX_ << " / " << coordY_;


    boulet_ = glGenLists(1);
    glNewList(boulet_, GL_COMPILE);
    glPushMatrix();
    glRotatef(axe_-180, 0, 0, 1);
    glTranslatef(0, coordX_, coordY_);
    //glColor3f(.55, .55, .55);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texturePierre_);
    GLUquadric* bou = gluNewQuadric();
    gluQuadricTexture(bou,GL_TRUE);
    glScalef(.1, .1, .1);
    gluSphere(bou, 3, 10, 10);
    gluDeleteQuadric(bou);
    glDisable(GL_TEXTURE_2D);
    if(finTrajectoire_)
    {
        glTranslatef(0, 0, -1.9);
        glColor3f(1, 0, 0);
        glRotatef(45, 0, 0, 1);
        glRectf(-6, -2.5, 6, 2.5);
        glRotatef(90, 0, 0, 1);
        glRectf(-6, -2.5, 6, 2.5);

    }
    glScalef(10, 10, 10);


    glColor3f(1, 1, 1);

    glPopMatrix();

    glEndList();

    return boulet_;
    glDeleteLists(boulet_,1);
}

void Boulet::reset()
{
    t_ = 0;
    coordX_ = 2.4;
    coordY_ = 10.8;
    axe_ = 180;
    finTrajectoire_ = false;
    cibleTouchee_=false;
}
