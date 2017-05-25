#include "trebuchet.h"

#include<QString>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "textures.h"
Trebuchet::Trebuchet()
{

}

Trebuchet::~Trebuchet(){
   glDeleteLists(completeTrebuchet_, 1);

}

void Trebuchet::setTexture(){
    QString chemin[3];
    const QString CHEMIN = ":/images";
    chemin[0]=CHEMIN+"/bois.bmp";
    chemin[1]=CHEMIN+"/pelouse.bmp";
    chemin[2]=CHEMIN+"/bois2.bmp";

    for(int i = 0;i<3;i++){
        Textures *tex=new Textures(chemin[i]);
       texture_[i]=tex->getTextures();
        delete tex;
    }


}



GLuint Trebuchet::draw(GLuint corde,int levierRotation){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    this->setTexture();

    Box *a=new Box(1,1,1, texture_[0]);
    Box *g=new Box(1,1,1, texture_[2]);

    GLuint levierBois=g->getCompleteBox();
    GLuint boxBois=a->getCompleteBox();

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
/*
    delete g;
    delete a;
    delete &levierBois;
    delete &boxBois;
*/

     return completeTrebuchet_;
     glDeleteLists(completeTrebuchet_, 1);
     glDeleteLists(levierBois, 1);
     glDeleteLists(boxBois, 1);

}
GLuint Trebuchet::getCompleteTrebuchet(){
    return completeTrebuchet_;
}
