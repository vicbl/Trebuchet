#include "cible.h"
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>

#include <QDebug>
Cible::Cible()
{

}

Cible::~Cible(){
    glDeleteLists(completeCible_, 1);
    glDeleteLists(cible_, 1);
}

void Cible::setTexture(Textures tex){
    this->textureBois_=tex.getTextures(0);
    this->textureCible_=tex.getTextures(9);
}

void Cible::drawPart(){
    cible_ = glGenLists(1);
    glNewList(cible_, GL_COMPILE);
        glPushMatrix();
            glScaled(2,2,2);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, this->textureCible_);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0,0,0);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(1,0,0);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(1,1,0);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(0,1,0);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glScaled(.5,.5,.5);
        glPopMatrix();
    glEndList();
   // glDeleteLists(cible_, 1);
}

void Cible::draw(){
     qDebug()<<"Draw Cible";
    this->drawPart();
    Box *a=new Box(1,1,1, this->textureBois_);
    GLuint boxBois=a->getCompleteBox();

    completeCible_ = glGenLists(1);
    glNewList(completeCible_, GL_COMPILE);
        glPushMatrix();
            //*********** Draw Cible*************
            glPushMatrix();
                glRotatef( 45, -1, 0, 0);
                glScalef( .1 ,.1 ,2);
                glCallList(boxBois);
                glScalef( 10 ,10 ,.5);
                glPushMatrix();
                    glTranslatef( -0.9, -0.06, -0.9);
                    glRotatef( 90, 1, 0, 0);
                    glScalef( 1.8 ,1.8 ,1);
                    glCallList(cible_);
                glPopMatrix();
            glPopMatrix();
            //************ End draw cible********

            //************Draw Support********
            glPushMatrix();
                glTranslatef( 0, 0.60, 0);
                glPushMatrix();
                    glTranslatef( 0.5, 0.5, 0);
                    glRotatef( 45, 1, -1, 0);
                    glScalef( .1 ,.1 ,1.8);
                    glCallList(boxBois);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef( -0.5, 0.5, 0);
                    glRotatef( 45, 1, 1, 0);
                    glScalef( .1 ,.1 ,1.8);
                    glCallList(boxBois);
                glPopMatrix();
           glPopMatrix();
           //************End Draw Support********
        glPopMatrix();
    glEndList();
    //delete a;


}
GLuint Cible::getCompleteCible(){
    return completeCible_;
}
