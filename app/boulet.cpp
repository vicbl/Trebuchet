#include "boulet.h"
#include <QOpenGLTexture>

#include <QtOpenGL/qgl.h>
#include <QDebug>
#include "game.h"

#define PI 3.14159265
Boulet::Boulet()
{

}

float Boulet::get_x() {return (float)coord_x;}  // Boulet entre 33 et 102
float Boulet::get_y() {return (float)coord_y;}

void Boulet::set_y(float y){coord_y=y;}
void Boulet::set_x(float x){coord_x=x;}

bool Boulet::getFin(){return finTrajectoire;}

void Boulet::set_v0(float v){v0=v;}
void Boulet::set_axe(int a){axe=a;}

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


        float newx = 2.4 + v0*cosa*t;               // x = x0 + v0*cos(a)*t
        float newy = 10.8 + v0*sina*t-.02*pow(t,2);     // y = y0 + v0*sin(a)*t + 1/2*g*t²


        if(newy>0 && !finTrajectoire )
        {
            coord_x = newx;
            coord_y = newy;
            if(slowMode){
                t=t+0.3;
            }else{
                t=t+1;
            }
            if (newy<3){
                 game_->calculScore(coord_x,coord_y);
            }

        } else
        {
            finTrajectoire = true;

        }


    }


    // qDebug() << "Boulet : " << coord_x << " / " << coord_y;


    boulet = glGenLists(1);
    glNewList(boulet, GL_COMPILE);
    glPushMatrix();
    glRotatef(axe-180, 0, 0, 1);
    glTranslatef(0, coord_x, coord_y);
    //glColor3f(.55, .55, .55);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texturePierre_);
    GLUquadric* bou = gluNewQuadric();
    gluQuadricTexture(bou,GL_TRUE);
    glScalef(.1, .1, .1);
    gluSphere(bou, 3, 10, 10);
    gluDeleteQuadric(bou);
    glDisable(GL_TEXTURE_2D);
    if(finTrajectoire)
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

    return boulet;
    glDeleteLists(boulet,1);
}

void Boulet::reset()
{
    t = 0;
    coord_x = 2.4;
    coord_y = 10.8;
    axe = 180;
    finTrajectoire = false;
    cibleTouchee_=false;
}
