#include "trebuchet.h"

#include<QString>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "textures.h"
#include <QDebug>
Trebuchet::Trebuchet()
{


}

Trebuchet::~Trebuchet(){


    glDeleteLists(completeTrebuchet_, 1);

}

void Trebuchet::setTexture(Textures tex){
    this->textureBois_=tex.getTextures(0);
       this->textureLevier_=tex.getTextures(1);
       this->textureContrePoids_=tex.getTextures(3);
       this->texturePierre_=tex.getTextures(12);
}



GLuint Trebuchet::draw(GLuint corde,int levierRotation){
    Box *a=new Box(1,1,1, this->textureLevier_);
    Box *b=new Box(1,1,1, this->textureBois_);
    Box *c=new Box(1,1,1, this->textureContrePoids_);
    GLuint levierBois=a->getCompleteBox();
    GLuint boxBois=b->getCompleteBox();
    GLuint contrePoids=c->getCompleteBox();

     GLuint roulette;
    roulette = glGenLists(1);
    glNewList(roulette, GL_COMPILE);
        glPushMatrix(); // roue arrière gauche
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, this->texturePierre_);
            GLUquadric* roue = gluNewQuadric();
            gluQuadricTexture(roue,GL_TRUE);
            glColor4f (1, 1, 1, 0.8);
            gluCylinder(roue, .8, .8, .8, 10, 10);
            glTranslatef(0, 0, .8);
            gluCylinder(roue, .8, 0, .1, 10, 10);
            gluDeleteQuadric(roue);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    glEndList();

    completeTrebuchet_ = glGenLists(1);
    glNewList(completeTrebuchet_, GL_COMPILE);


        // Roues
    glPushMatrix();
        glScalef(.1, .1, .1);
        glTranslatef(0, 0, -0.1);
        glRotatef(90, 0, 1, 0);

        glTranslatef(0, 4, 2.5);
        glCallList(roulette);
        glTranslatef(0, -8, 0);
        glCallList(roulette);
        glRotatef(180, 0, 1, 0);
        glTranslatef(0, 0, 5);
        glCallList(roulette);
        glTranslatef(0, 8, 0);
        glCallList(roulette);
    glPopMatrix();

       // socle
    glScalef(0.5,1,0.05);
    glCallList(boxBois);
    glPushMatrix();
    glScalef(2,1,20);
    // pieds
    glPushMatrix();
        glTranslatef( .22, -0.23, .43);
        glRotatef( 62, 1, 0, 0);
        glScalef( 0.05 ,1 ,.05);
        glCallList(boxBois);
    glPopMatrix();

    glPushMatrix();
        glTranslatef( .22, 0.23, .43);
        glRotatef( -62, 1, 0, 0);
        glScalef( 0.05 ,1 ,.05);
        glCallList(boxBois);
    glPopMatrix();

    glPushMatrix();
        glTranslatef( -.22, -0.23, .43);
        glRotatef( 62, 1, 0, 0);
        glScalef( 0.05 ,1 ,.05);
        glCallList(boxBois);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -.22, 0.23, .43);
    glRotatef( -62, 1, 0, 0);
    glScalef( 0.05 ,1 ,.05);
    glCallList(boxBois);
    glPopMatrix();

    // bascule
    glPushMatrix ();
        glTranslatef(0,0,0.85);
        glRotatef(90,0,1,0);
        glScalef(0.02,0.02,0.5);
        glCallList(levierBois);
        // levier
            glPushMatrix ();
                glScalef(5,5,0.2);
                glRotatef(levierRotation,0,0,1);
                glPushMatrix ();
                    glTranslatef(0,4,0);

                    //corde relie contrepoids au balancier


                    //Contre poids
                    glPushMatrix();
                        glTranslatef(0, -8, 0);
                        glRotatef(-levierRotation, 0, 0, 1);
                        glRotatef(90, -1, 0, 0);
                        glPushMatrix();
                            glScalef(3,0.2,0.2);
                            glTranslatef(0, 0, .5);
                            GLUquadric* corde1 = gluNewQuadric();
                            glRotatef(90,0,1,0);
                            glColor4f (1, 1, 1, 0.8);
                            gluCylinder(corde1, 1, 1, 1, 100, 100);
                            gluDeleteQuadric(corde1);

                            glRotatef(-90,0,1,0);

                            glScalef(0.33,5,5);
                            glScalef(3, 3, 3);

                            glTranslatef(1.6, 0, 0);
                            glCallList(contrePoids);
                        glPopMatrix();
                    glPopMatrix();
                    glScalef(1,20,1);
                    //glColor3f(0,0,0);
                    glCallList(levierBois);

                glPopMatrix();
                // corde
                glPushMatrix ();
                    glTranslatef(.5, 13.5, 0);
                    glCallList(corde);
                glPopMatrix();
            glPopMatrix ();
        glPopMatrix();
        glPopMatrix();


    glEndList();

    return completeTrebuchet_;
    glDeleteLists(levierBois, 1);
    glDeleteLists(boxBois, 1);
    glDeleteLists(contrePoids, 1);
     glDeleteLists(roulette, 1);


}

