#include "pelouse.h"
#include"math.h"
#include <GL/gl.h>
#include <QDebug>
#include <time.h>
Pelouse::Pelouse()
{
    srand(time(NULL)); // initialisation de rand
    for (int colonne=0; colonne<10; colonne++)
    {
        for (int ligne=0; ligne<10; ligne++)
        {
                 temp[colonne][ligne] = rand() % (5);
        }
    }
}

Pelouse::~Pelouse(){
    glDeleteLists(pelouse_, 1);
}

void Pelouse::setTexture(Textures tex){
    this->texturePelouse1_= tex.getTextures(4);
    this->texturePelouse2_= tex.getTextures(5);
    this->texturePelouse3_= tex.getTextures(6);
    this->texturePelouse4_= tex.getTextures(7);
    this->texturePelouse5_= tex.getTextures(8);
}


void Pelouse::draw(){
     qDebug()<<"Draw Pelouse";
    int MAP_Y=500;
    int MAP_X=500;




    GLuint pelouse1 = glGenLists(1);
    glNewList(pelouse1, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texturePelouse1_);
        glPushMatrix();
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0,0,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(1,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1,1,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,1,0);
            glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glEndList();

    GLuint pelouse2 = glGenLists(1);
    glNewList(pelouse2, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texturePelouse2_);
        glPushMatrix();
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0,0,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(1,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1,1,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,1,0);
            glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glEndList();

    GLuint pelouse3 = glGenLists(1);
    glNewList(pelouse3, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texturePelouse3_);
        glPushMatrix();
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0,0,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(1,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1,1,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,1,0);
            glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glEndList();

    GLuint pelouse4 = glGenLists(1);
    glNewList(pelouse4, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texturePelouse4_);
        glPushMatrix();
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0,0,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(1,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1,1,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,1,0);
            glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glEndList();

    GLuint pelouse5 = glGenLists(1);
    glNewList(pelouse5, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texturePelouse5_);
        glPushMatrix();
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0,0,0);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(1,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(1,1,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,1,0);
            glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glEndList();

    pelouse_ = glGenLists(1);
    glNewList(pelouse_, GL_COMPILE);
        glPushMatrix();
        for (int colonne=0; colonne<10; colonne++)
        {
            for (int ligne=0; ligne<10; ligne++)
            {
                glPushMatrix();
                    glTranslatef(1*ligne,1*colonne,0);
                    if ( temp[colonne][ligne]==0){
                        glCallList(pelouse1);
                    }else if( temp[colonne][ligne]==1){
                        glCallList(pelouse2);
                    }
                    else if( temp[colonne][ligne]==2){
                        glCallList(pelouse3);
                    }
                    else if( temp[colonne][ligne]==3){
                        glCallList(pelouse4);
                    }
                    else {
                        glCallList(pelouse5);
                    }
                glPopMatrix();
            }
        }
        glPopMatrix();
    glEndList();
    /*glDeleteLists(pelouse1,1);
    glDeleteLists(pelouse2,1);
    glDeleteLists(pelouse3,1);
    glDeleteLists(pelouse4,1);
    glDeleteLists(pelouse5,1);*/


}
GLuint Pelouse::getPelouse(){
    return pelouse_;
}
