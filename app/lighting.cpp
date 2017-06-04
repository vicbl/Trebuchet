#include "lighting.h"

#include <GL/glu.h>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include <QDebug>
Lighting::Lighting()
{

}

Lighting::~Lighting(){
    glDeleteLists(lighting_,1);
}
void Lighting::setTexture(Textures tex){
     this->textureCiment_=tex.getTextures(10);
     this->textureProjecteur_=tex.getTextures(11);
}

void Lighting::draw(){
     qDebug()<<"Draw Lighting";
    Box *a=new Box(1,1,1, this->textureCiment_);
    GLuint piedProjecteur=a->getCompleteBox();
    Box *b=new Box(1,1,1, this->textureProjecteur_);
    GLuint projecteur=b->getCompleteBox();

    lighting_ = glGenLists(1);
    glNewList(lighting_, GL_COMPILE);
        glPushMatrix();
            glPushMatrix();
                glTranslatef(0,0,5);
                glScalef(0.4,0.4,10);
                glCallList(piedProjecteur);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0,0.5,10.5);
                glRotatef(-45,1,0,0);
                glPushMatrix();
                    glScalef(2,0.5,2);
                    glCallList(projecteur);
                glPopMatrix();

                GLUquadric* bou = gluNewQuadric();
                gluQuadricTexture(bou,GL_TRUE);
                glColor3f(1, 1, 1);
                //On dessine les ampoule du projecteur
                for(float i =0.80;i>=-0.81;i=i-0.40){
                    for(float j =0.80;j>=-0.81;j=j-0.40){
                        glPushMatrix();
                            glTranslatef(i,0.15,j);
                            gluSphere(bou, 0.20, 10, 10);
                        glPopMatrix();
                    }
                }
                gluDeleteQuadric(bou);
            glPopMatrix();
        glPopMatrix();
    glEndList();
    //delete a;
   // delete b;
}


GLuint Lighting::getCompleteLighting(){
    return lighting_;
}


