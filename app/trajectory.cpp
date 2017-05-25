#include "Trajectory.h"

#include <GL/glu.h>
#include <QtOpenGL/qgl.h>
#include <QDebug>
#define PI 3.14159265
Trajectory::Trajectory()
{

}

void Trajectory::set_v0(float v){v0=v;}
void Trajectory::set_axe(int a){axe=a;}

GLuint Trajectory::draw()
{
    float i=0;
    GLfloat coord_y = 7; // hauteur
    GLfloat coord_x = 1.7; // distance au trébuchet
    float cosa = cos(PI*20/180);
    float sina = sin(PI*20/180);

    trajectory_ = glGenLists(1);

    glNewList(trajectory_, GL_COMPILE);
        GLUquadric* bou = gluNewQuadric();
        glPushMatrix();
            glRotatef(axe-180, 0, 0, 1);
            glColor3f(.9, .9, .9);
            while (coord_y>0){
                glPushMatrix();
                    coord_x = 1.7 + v0*cosa*i;
                    coord_y = 7 + v0*sina*i-.02*pow(i,2);
                    i=i+0.1;
                    glTranslatef(0, coord_x, coord_y);
                    glScalef(.05, .05, .05);
                    gluSphere(bou, 1, 10, 10);
                    glScalef(10, 10, 10);
                glPopMatrix();
            }
            gluDeleteQuadric(bou);
            glColor3f(1, 1, 1);
        glPopMatrix();
    glEndList();
    return trajectory_;
    glDeleteLists(trajectory_, 1);
}


