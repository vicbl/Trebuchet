#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glu.h>
#include<QString>

#include<iostream>
using namespace std;

class Textures
{
private:
 GLuint texture_;
public:
    Textures(const QString ch);
    GLuint getTextures();
   ~Textures();
};

#endif // TEXTURES_H
