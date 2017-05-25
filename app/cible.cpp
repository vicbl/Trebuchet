#include "cible.h"
#include<QString>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "textures.h"
Cible::Cible()
{


}

Cible::~Cible(){
    glDeleteLists(completeCible_, 1);
    glDeleteLists(cible_, 1);
}

void Cible::setTexture(){
    textureBois_=((Textures(":/images/bois.bmp")).getTextures());
    textureCible_=((Textures(":/images/cible.bmp")).getTextures());
}

void Cible::drawPart(){
    cible_ = glGenLists(1);
    glNewList(cible_, GL_COMPILE);
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureCible_);
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
        glPopMatrix();
    glEndList();
}

void Cible::draw(){

    this->setTexture();
    this->drawPart();
    Box *a=new Box(1,1,1, textureBois_);
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
}
GLuint Cible::getCompleteCible(){
    return completeCible_;
}
