#include "pelouse.h"
#include"math.h"
#include <GL/gl.h>
#include <QDebug>

Pelouse::Pelouse()
{

   /* int elems=1000;
    int centre = elems/2;
    int altitude=15;
    float max=0;
    for(int x=0; x<elems; x++)
    {
        altitude=15;
        for(int y=0; y<elems; y++)
        {
            // if ((x<centre-75 || x>centre+75)||(y>100)){// en dehors de la zone de tir

            //altitude=altitude+2;
            terrain[x][y]= 0.05*(rand()%altitude);

            if(altitude>max){
                max=altitude;
            }

            // }
            // else{
            //     terrain[x][y]= 0;
            // }

        }

    }
    qDebug()<<"Altitude max="<<max;*/
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
                glVertex3f(0.25,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(0.25,0.25,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,0.25,0);
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
                glVertex3f(0.25,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(0.25,0.25,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,0.25,0);
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
                glVertex3f(0.25,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(0.25,0.25,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,0.25,0);
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
                glVertex3f(0.25,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(0.25,0.25,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,0.25,0);
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
                glVertex3f(0.25,0,0);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(0.25,0.25,0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0,0.25,0);
            glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glEndList();


   /* int max=0;

        for (int x = 0; x < MAP_X-1; x++)
        {
        float i=1;

            for (int y = 0; y < MAP_Y-1; y++)
            {

              if ((x<500-75 || x>500+75)||(y>100)){

                        i=i+0.001;
                        glColor3f(i, i, i);

                       // texturePelouse_=((Textures(":/images/pierre.bmp")).getTextures());
                }else
                {


                   //texturePelouse_=((Textures(":/images/pelouse.bmp")).getTextures());
                    glColor3f(1.0, 1.0,1.0);
                }
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texturePelouse_);
                 glBegin(GL_TRIANGLE_STRIP);
                // draw vertex 0
                //glColor3f(terrain[x][z][1]/255.0f, terrain[x][z][1]/255.0f, terrain[x][z][1]/255.0f);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(x, y, terrain[x][y]);

                // draw vertex 1
                glTexCoord2f(1.0f, 0.0f);
                //glColor3f(terrain[x+1][z][1]/255.0f, terrain[x+1][z][1]/255.0f, terrain[x+1][z][1]/255.0f);
                glVertex3f(x+1, y, terrain[x+1][y]);

                // draw vertex 2
                glTexCoord2f(0.0f, 1.0f);
                //  glColor3f(terrain[x][z+1][1]/255.0f, terrain[x][z+1][1]/255.0f, terrain[x][z+1][1]/255.0f);
                glVertex3f(x, y+1, terrain[x][y+1]);

                // draw vertex 3
                // glColor3f(terrain[x+1][z+1][1]/255.0f, terrain[x+1][z+1][1]/255.0f, terrain[x+1][z+1][1]/255.0f);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(x+1, y+1, terrain[x+1][y+1]);
                 glEnd();
            }

        }*/


    pelouse_ = glGenLists(1);
    glNewList(pelouse_, GL_COMPILE);
        glPushMatrix();
        for (int colonne=-100; colonne<300; colonne++)
        {
            for (int ligne=-150; ligne<150; ligne++)
            {
                glPushMatrix();
                    glTranslatef(0.25*ligne,0.25*colonne,0);
                    if (firstPassage_){
                        temp[colonne+100][ligne+150] = rand() % (5);
                    }
                    //qDebug()<<"temp"<<temp[colonne+100][ligne+150];
                    if ( temp[colonne+100][ligne+150]==0){
                        glCallList(pelouse1);
                    }else if( temp[colonne+100][ligne+150]==1){
                        glCallList(pelouse2);
                    }
                    else if( temp[colonne+100][ligne+150]==2){
                        glCallList(pelouse3);
                    }
                    else if( temp[colonne+100][ligne+150]==3){
                        glCallList(pelouse4);
                    }
                    else {
                        glCallList(pelouse5);
                    }
                glPopMatrix();
            }
        }
        firstPassage_=false;
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
