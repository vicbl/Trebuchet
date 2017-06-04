#ifndef PELOUSE_H
#define PELOUSE_H
#include "textures.h"
#include <GL/glu.h>
class Pelouse
{
private:
    int temp[1000][1000];
    GLuint pelouse_;
    GLuint texturePelouse1_;
    GLuint texturePelouse2_;
    GLuint texturePelouse3_;
    GLuint texturePelouse4_;
    GLuint texturePelouse5_;

public:
    Pelouse();
    void draw();
    void setTexture(Textures tex);
    GLuint getPelouse();
    ~Pelouse();

};
#endif // PELOUSE_H
