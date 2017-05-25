#include "boulet.h"

#include <GL/glu.h>
#include <QtOpenGL/qgl.h>
#include <QDebug>

Boulet::Boulet()
{

}

float Boulet::get_x() {return (float)coord_x;}  // Boulet entre 29 et 80
float Boulet::get_y() {return (float)coord_y;}

void Boulet::set_y(float y){coord_y=y;}
void Boulet::set_x(float x){coord_x=x;}

bool Boulet::getFin(){return finTrajectoire;}

void Boulet::set_v0(float v){v0=v;}
void Boulet::set_axe(int a){axe=a;}

GLuint Boulet::draw()
{
    boulet = glGenLists(1);

    // Calcul des nouvelles coordonnées

    float cosa = cos(3.1415*20/180);
    float sina = sin(3.1415*20/180);

    float newx = 1.7 + v0*cosa*t;               // x = x0 + v0*cos(a)*t
    float newy = 7 + v0*sina*t-.02*pow(t,2);     // y = y0 + v0*sin(a)*t + 1/2*g*t²

    if(newy>0 && !finTrajectoire)
    {
        coord_x = newx;
        coord_y = newy;
        t=t+1;
    } else
    {
        finTrajectoire = true;
        coord_y = 0.2;
    }



   // qDebug() << "Boulet : " << coord_x << " / " << coord_y;

    glNewList(boulet, GL_COMPILE);

        glPushMatrix();

            glRotatef(axe-180, 0, 0, 1);
            glTranslatef(0, coord_x, coord_y);
            glColor3f(.55, .55, .55);
            GLUquadric* bou = gluNewQuadric();
            glScalef(.1, .1, .1);
            gluSphere(bou, 3, 10, 10);

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
            gluDeleteQuadric(bou);
            glColor3f(1, 1, 1);

        glPopMatrix();

    glEndList();

    return boulet;
}

void Boulet::reset()
{
    t = 0;
    coord_x = 1.7;
    coord_y = 7;
    axe = 180;
    finTrajectoire = false;
}
