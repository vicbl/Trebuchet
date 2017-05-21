#include "logotelecom.h"

#include<QString>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "textures.h"
#include "box.h"
LogoTelecom::LogoTelecom()
{


}

LogoTelecom::~LogoTelecom(){
   // glDeleteLists(completeLogoTelecom_, 1);

}

void LogoTelecom::setTexture(){
    QString chemin[3];
    const QString CHEMIN = ":/images";
    chemin[0]=CHEMIN+"/bois.bmp";
    chemin[1]=CHEMIN+"/TSE.bmp";
    chemin[2]=CHEMIN+"/UJM.bmp";

    for(int i = 0;i<3;i++){
        Textures *tex=new Textures(chemin[i]);
       texture_[i]=tex->getTextures();
        //delete tex;
    }

}

void LogoTelecom::drawPartTSE(){

    logoTelecom_ = glGenLists(1);
    glNewList(logoTelecom_, GL_COMPILE);
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_[1]);
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
void LogoTelecom::drawPartUJM(){

    logoUJM_ = glGenLists(1);
    glNewList(logoUJM_, GL_COMPILE);
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

GLuint LogoTelecom::draw(){

    this->setTexture();
    this->drawPartTSE();
    this->drawPartUJM();
    Box *a=new Box(1,1,1, texture_[0]);
    GLuint boxBois=a->getCompleteBox();

    completeLogoTelecom_ = glGenLists(1);
    glNewList(completeLogoTelecom_, GL_COMPILE);

    glPushMatrix();
        //***********Support***********
        glPushMatrix();
            glPushMatrix();
                glTranslatef( 0.525, 0, 0);
                glScalef( .06 ,.06 ,1);
                glCallList(boxBois);
            glPopMatrix();
            glPushMatrix();
                glTranslatef( -0.525,0, 0);
                glScalef( .06 ,.06 ,1);
                glCallList(boxBois);
            glPopMatrix();
        glPopMatrix();
        //***********End Support***********

        //***********Banderole***********
        glPushMatrix();
            glPushMatrix();
                glTranslatef(0, 0, -0.05);
                glRotatef( 90, 1, 0, 0);
                glScalef( .5 ,.5 ,.5);
                glCallList(logoTelecom_);
            glPopMatrix();
            glPushMatrix();
                glTranslatef( -0.5,0, -0.05);
                glRotatef( 90, 1, 0, 0);
                glScalef( .5,.5 ,.5);
                glCallList(logoUJM_);
            glPopMatrix();
        glPopMatrix();
        //***********End Banderole***********
    glPopMatrix();
    glEndList();
    return completeLogoTelecom_;
}
GLuint LogoTelecom::getCompleteLogoTelecom(){
    return completeLogoTelecom_;
}

