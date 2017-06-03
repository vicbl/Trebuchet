#include "logotelecom.h"
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "textures.h"
#include <QString>
#include "box.h"
LogoTelecom::LogoTelecom()
{

}

LogoTelecom::~LogoTelecom(){
    glDeleteLists(completeLogoTelecom_, 1);
    glDeleteLists(logoTelecom_, 1);
    glDeleteLists(logoUJM_, 1);
}

void LogoTelecom::setTexture(){
    textureBois_=((Textures(":/images/bois.bmp")).getTextures());
    textureTSE_=((Textures(":/images/TSE.bmp")).getTextures());
    textureUJM_=((Textures(":/images/UJM.bmp")).getTextures());
}

void LogoTelecom::drawPartTSE(){
    logoTelecom_ = glGenLists(1);
    glNewList(logoTelecom_, GL_COMPILE);
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureTSE_);
            glBegin(GL_QUADS);
                glNormal3d ( 0,0,1 );
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
            glBindTexture(GL_TEXTURE_2D, textureUJM_);
            glBegin(GL_QUADS);
                glNormal3d ( 0,0,1 );
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

void LogoTelecom::draw(){

    setTexture();
    drawPartTSE();
    drawPartUJM();

    Box *a=new  Box(1,1,1, textureBois_);
    boxBois=a->getCompleteBox();
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
    //return completeLogoTelecom_;
}
GLuint LogoTelecom::getCompleteLogoTelecom(){
    return completeLogoTelecom_;
}

