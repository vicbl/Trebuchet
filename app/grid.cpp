#include "grid.h"
#include <QOpenGLTexture>
#include <QtOpenGL/qgl.h>
#include <QtOpenGL>
Grid::Grid(int nbLines,int nbColumns, double width)
{
    this->nbLines_=nbLines;
    this->nbColumns_=nbColumns;
    this->width_=width;
}
Grid::~Grid(){
    glDeleteLists(gridPart_, 1);
    glDeleteLists(completeGrid_, 1);
}

void Grid::drawGridPart(){
    double smallWidth=width_;
    double longWidth=1-width_;
    gridPart_ = glGenLists(1);
    glNewList(gridPart_, GL_COMPILE);
        glPushMatrix();
            glScalef(1,1,0.05);
            glColor3f(0,0,0);
            glBegin(GL_QUADS);
                glVertex3f(0,0,0);
                glVertex3f(smallWidth,0,0);
                glVertex3f(smallWidth,1,0);
                glVertex3f(0,1,0);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(smallWidth,1,0);
                glVertex3f(smallWidth,longWidth,0);
                glVertex3f(longWidth,longWidth,0);
                glVertex3f(longWidth,1,0);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(longWidth,0,0);
                glVertex3f(longWidth,smallWidth,0);
                glVertex3f(smallWidth,smallWidth,0);
                glVertex3f(smallWidth,0,0);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(longWidth,0,0);
                glVertex3f(1,0,0);
                glVertex3f(1,1,0);
                glVertex3f(longWidth,1,0);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(0,0,0);
                glVertex3f(0,0,1);
                glVertex3f(1,0,1);
                glVertex3f(1,0,0);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(0,0,0);
                glVertex3f(0,1,0);
                glVertex3f(0,1,1);
                glVertex3f(0,0,1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(0,1,0);
                glVertex3f(1,1,0);
                glVertex3f(1,1,1);
                glVertex3f(0,1,1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(1,0,0);
                glVertex3f(1,0,1);
                glVertex3f(1,1,1);
                glVertex3f(1,1,0);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(1,0,1);
                glVertex3f(0,0,1);
                glVertex3f(0,smallWidth,1);
                glVertex3f(1,smallWidth,1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(1,smallWidth,1);
                glVertex3f(longWidth,smallWidth,1);
                glVertex3f(longWidth,longWidth,1);
                glVertex3f(1,longWidth,1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(smallWidth,smallWidth,1);
                glVertex3f(0,smallWidth,1);
                glVertex3f(0,longWidth,1);
                glVertex3f(smallWidth,longWidth,1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(1,longWidth,1);
                glVertex3f(0,longWidth,1);
                glVertex3f(0,1,1);
                glVertex3f(1,1,1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(smallWidth,longWidth,0);
                glVertex3f(smallWidth,smallWidth,0);
                glVertex3f(smallWidth,smallWidth,1);
                glVertex3f(smallWidth,longWidth,1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(smallWidth,smallWidth,0);
                glVertex3f(longWidth,smallWidth,0);
                glVertex3f(longWidth,smallWidth,1);
                glVertex3f(smallWidth,smallWidth,1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(longWidth,smallWidth,0);
                glVertex3f(longWidth,longWidth,0);
                glVertex3f(longWidth,longWidth,1);
                glVertex3f(longWidth,smallWidth,1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(smallWidth,longWidth,0);
                glVertex3f(longWidth,longWidth,0);
                glVertex3f(longWidth,longWidth,1);
                glVertex3f(smallWidth,longWidth,1);
            glEnd();
        glPopMatrix();
    glEndList();

}

void Grid::draw(){
    this->drawGridPart();
    completeGrid_ = glGenLists(1);
    glNewList(completeGrid_, GL_COMPILE);
        glPushMatrix();
            for (int column=0; column<nbColumns_; column++)
            {
                for (int line=0; line<nbLines_; line++)
                {
                    glPushMatrix();
                    glTranslatef(column,line,0);
                    glCallList(gridPart_);
                    glPopMatrix();
                }
            }
        glPopMatrix();
    glEndList();
}

GLuint Grid::getCompleteGrid(){
    return completeGrid_;
}
