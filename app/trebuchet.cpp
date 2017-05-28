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

void Trebuchet::setTexture(){
    textureBois_=((Textures(":/images/bois.bmp")).getTextures());
    textureLevier_=((Textures(":/images/bois2.bmp")).getTextures());
    textureContrePoids_=((Textures(":/images/bois4.bmp")).getTextures());
}



GLuint Trebuchet::draw(GLuint corde,int levierRotation){


    this->setTexture();

    Box *a=new Box(1,1,1, textureLevier_);
    Box *b=new Box(1,1,1, textureBois_);
    Box *c=new Box(1,1,1, textureContrePoids_);
    GLuint levierBois=a->getCompleteBox();
    GLuint boxBois=b->getCompleteBox();
    GLuint contrePoids=c->getCompleteBox();

    completeTrebuchet_ = glGenLists(1);
    glNewList(completeTrebuchet_, GL_COMPILE);
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

                    //Contre poids
                    glPushMatrix();

                      glTranslatef(3, -8, 0);
                      int decalageAttache=-4;

                        if (levierRotation>30){
                            if (levierRotation>40){
                                if (levierRotation>50){
                                    if (levierRotation>60){
                                        if (levierRotation>70){
                                            if (levierRotation>80){
                                                if (levierRotation>90){
                                                    if (levierRotation>100){
                                                        decalageAttache=-3;
                                                        if (levierRotation>110){
                                                            if (levierRotation>120){
                                                                glTranslatef(0.1,-2,0);
                                                                glRotatef(-levierRotation*0.1,0,0,1);
                                                            }else{
                                                                glTranslatef(0.2,-1.5,0);
                                                                glRotatef(-levierRotation*0.2,0,0,1);
                                                            }
                                                        }else{
                                                            glTranslatef(0.3,-1.4,0);
                                                            glRotatef(-levierRotation*0.3,0,0,1);
                                                        }
                                                    }else{
                                                        glTranslatef(0.4,-1.3,0);
                                                        glRotatef(-levierRotation*0.4,0,0,1);
                                                    }
                                                }else{
                                                    glTranslatef(0.5,-1,0);
                                                    glRotatef(-levierRotation*0.5,0,0,1);
                                                }
                                            }else{
                                                glTranslatef(0.5,-0.9,0);
                                                glRotatef(-levierRotation*0.5,0,0,1);
                                            }
                                        }else{
                                            glTranslatef(0.5,-0.8,0);
                                            glRotatef(-levierRotation*0.6,0,0,1);
                                        }
                                    }else{
                                        glTranslatef(0.5,-0.7,0);
                                        glRotatef(-levierRotation*0.7,0,0,1);
                                    }
                                }else{
                                    glTranslatef(0.5,-0.6,0);
                                    glRotatef(-levierRotation*0.8,0,0,1);
                                }
                            }else{
                                glTranslatef(0.5,-0.5,0);
                                glRotatef(-levierRotation*0.9,0,0,1);
                            }
                        }else{
                            glTranslatef(0.5,-0.4,0);
                            glRotatef(-levierRotation,0,0,1);
                        }


                        //corde relie contrepoids au balancier


                        glPushMatrix();
                            GLUquadric* corde1 = gluNewQuadric();
                            glTranslatef(decalageAttache,0,0);
                            glScalef(3,0.2,0.2);
                            glRotatef(90,0,1,0);
                            glColor4f (1, 1, 1, 0.8);
                            gluCylinder(corde1, 1, 1, 1, 100, 100);
                            gluDeleteQuadric(corde1);
                        glPopMatrix();


                        glScalef(3, 3, 3);
                        glCallList(contrePoids);
                    glPopMatrix();
                    glScalef(1,20,1);
                    //glColor3f(0,0,0);
                    glCallList(levierBois);



//                    glScalef(4, 0.05, 1);
//                    glTranslatef(.5, -9, 0);
//                    glRotatef(90, 0, 1, 0);
//                    float angcp = levierRotation;
//                    glRotatef(angcp, 0, 0, 1);
//                    GLUquadric *cp= gluNewQuadric();
//                    gluCylinder(cp, .15, .15, 1, 10, 10);
//                    gluDeleteQuadric(cp);
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
    glDeleteLists(completeTrebuchet_, 1);

}
GLuint Trebuchet::getCompleteTrebuchet(){
}

