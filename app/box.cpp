#include "box.h"
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
Box::Box(double width, double height, double thickness, GLuint texture)
{
    this->width_=width;
    this->height_=height;
    this->thickness_=thickness;
    this->texture_=texture;
    this->draw();
}
Box::~Box(){
    glDeleteLists(completeBox_, 1);
}
void Box::draw(){
    completeBox_ = glGenLists(1);
    glNewList(completeBox_, GL_COMPILE);
        glPushMatrix();
            glTranslatef(-0.5, -.5, -.5);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_);
            glBegin(GL_QUADS);
                glNormal3f ( 0,0,1 );
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0,0,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(1,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1,1,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,1,0);
            glEnd();
            glBegin(GL_QUADS);
                 glNormal3f ( 0,0,1 );
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0,0,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(0,0,1);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1,0,1);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(1,0,0);
            glEnd();
            glBegin(GL_QUADS);
                 glNormal3f ( 0,0,1 );
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0,0,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(0,1,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(0,1,1);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,0,1);
            glEnd();
            glBegin(GL_QUADS);
                 glNormal3f ( 0,0,1 );
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0,1,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(1,1,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1,1,1);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,1,1);
            glEnd();
            glBegin(GL_QUADS);
                 glNormal3f ( 0,0,1 );
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(1,0,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(1,0,1);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1,1,1);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(1,1,0);
            glEnd();
            glBegin(GL_QUADS);
                 glNormal3f ( 0,0,1 );
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(1,0,1);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(0,0,1);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(0,1,1);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(1,1,1);
            glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glEndList();
}

GLuint Box::getCompleteBox(){
    return completeBox_;
}
