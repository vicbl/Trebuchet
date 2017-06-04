#include "textures.h"

#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include <QtOpenGL>
#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include "myglwidget.h"
#include "ui_window.h"
#include <GL/glu.h>
#include <QDebug>

Textures::Textures()
{

   /* QImage img;

    glGenTextures(1, &texture_);


    if( ! img.load(ch) )
    {
        std::cerr << "error loading textures" <<  std::endl ;
        //exit( 1 );
    }

    QImage GL_formatted_image;
    GL_formatted_image = QGLWidget::convertToGLFormat(img);
    if( GL_formatted_image.isNull() )
    {
        std::cerr << "error GL_formatted_image" << std::endl ;
        //exit( 1 );
    }

    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
                  GL_formatted_image.width(), GL_formatted_image.height(),
                  0, GL_RGBA, GL_UNSIGNED_BYTE, GL_formatted_image.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );*/

}
void Textures::setTextures(){
    QString chemin[15];

    chemin[0]=":/images/bois.bmp";
    chemin[1]=":/images/bois2.bmp";
    chemin[2]=":/images/bois3.bmp";
    chemin[3]=":/images/bois4.bmp";
    chemin[4]=":/images/pelouse1.bmp";
    chemin[5]=":/images/pelouse2.bmp";
    chemin[6]=":/images/pelouse3.bmp";
    chemin[7]=":/images/pelouse4.bmp";
    chemin[8]=":/images/pelouse5.bmp";
    chemin[9]=":/images/cible.bmp";
    chemin[10]=":/images/concrete.bmp";
    chemin[11]=":/images/aluminium.bmp";
    chemin[12]=":/images/pierre.bmp";
    chemin[13]=":/images/TSE2.bmp";
    chemin[14]=":/images/UJM.bmp";



    glGenTextures(15, textureA_);

    QImage img;
    for(int i = 0;i<15;i++){

        if( ! img.load(chemin[i]) )
        {
            std::cerr << "error loading " <<  std::endl ;
            exit( 1 );
        }

        QImage GL_formatted_image;
        GL_formatted_image = QGLWidget::convertToGLFormat(img);
        if( GL_formatted_image.isNull() )
        {
            std::cerr << "error GL_formatted_image" << std::endl ;
            //   exit( 1 );
        }


        // glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureA_[i]);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
                      GL_formatted_image.width(), GL_formatted_image.height(),
                      0, GL_RGBA, GL_UNSIGNED_BYTE, GL_formatted_image.bits() );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }


}

GLuint Textures::getTextures(int numTexture){
    return textureA_[numTexture];
}


Textures::~Textures(){

}
