#include "pelouse.h"
#include<QString>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "textures.h"
Pelouse::Pelouse()
{

}

Pelouse::~Pelouse(){
    glDeleteLists(pelouse_, 1);
}

void Pelouse::setTexture(){
    texturePelouse_=((Textures(":/images/pelouse.bmp")).getTextures());
}


void Pelouse::draw(){
    this->setTexture();

    pelouse_ = glGenLists(1);

    glNewList(pelouse_, GL_COMPILE);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturePelouse_);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0,0,0);
            glTexCoord2f(10.0f, 0.0f);
            glVertex3f(10,0,0);
            glTexCoord2f(10.0f, 10.0f);
            glVertex3f(10,10,0);
            glTexCoord2f(0.0f, 10.0f);
            glVertex3f(0,10,0);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEndList();

}
GLuint Pelouse::getPelouse(){
    return pelouse_;
}
