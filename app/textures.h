#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glu.h>
#include<QString>

#include<iostream>
using namespace std;

class Textures
{
private:

    GLuint  textureA_[15];
    GLuint  texture_;
public:
    Textures();
    GLuint getTextures(int numTexture);
    void setTextures();
   ~Textures();
};

#endif // TEXTURES_H
