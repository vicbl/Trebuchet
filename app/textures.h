#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glu.h>
#include<QString>

#include<iostream>
using namespace std;

class Textures
{
private:
    GLuint  texture_[15];

public:
    Textures();
    GLuint getTextures(int numTexture);
   ~Textures();
};

#endif // TEXTURES_H
