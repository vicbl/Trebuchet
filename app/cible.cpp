#include "cible.h"
#include<QString>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "textures.h"
Cible::Cible()
{


}

Cible::~Cible(){
   // glDeleteLists(completeCible_, 1);

}

void Cible::setTexture(){
    QString chemin[3];
    const QString CHEMIN = ":/images";
    chemin[0]=CHEMIN+"/bois.bmp";
    chemin[1]=CHEMIN+"/pelouse.bmp";
    chemin[2]=CHEMIN+"/cible.bmp";

    for(int i = 0;i<3;i++){
        Textures *tex=new Textures(chemin[i]);
       texture_[i]=tex->getTextures();
        //delete tex;
    }

}

void Cible::drawPart(){

    cible_ = glGenLists(1);
    glNewList(cible_, GL_COMPILE);
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_[2]);



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

GLuint Cible::draw(){

    this->setTexture();
    this->drawPart();
    Box *a=new Box(1,1,1, texture_[0]);
    GLuint boxBois=a->getCompleteBox();

    completeCible_ = glGenLists(1);
    glNewList(completeCible_, GL_COMPILE);

    glPushMatrix();

        //Cible
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

        //Support
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
    glPopMatrix();






    glEndList();

     return completeCible_;
}
GLuint Cible::getCompleteCible(){
    return completeCible_;
}
