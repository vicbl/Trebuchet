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

Textures::Textures(const QString ch)
{
    QImage img;

    glGenTextures(1, &texture_);


        if( ! img.load(ch) )
        {
            std::cerr << "error loading textures" <<  std::endl ;
            exit( 1 );
        }

        QImage GL_formatted_image;
        GL_formatted_image = QGLWidget::convertToGLFormat(img);
        if( GL_formatted_image.isNull() )
        {
            std::cerr << "error GL_formatted_image" << std::endl ;
            exit( 1 );
        }

        glBindTexture(GL_TEXTURE_2D, texture_);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
                      GL_formatted_image.width(), GL_formatted_image.height(),
                      0, GL_RGBA, GL_UNSIGNED_BYTE, GL_formatted_image.bits() );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

}


GLuint Textures::getTextures(){
    return texture_;
}


Textures::~Textures(){

}
