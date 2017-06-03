#ifndef PELOUSE_H
#define PELOUSE_H

#include <GL/glu.h>
class Pelouse
{
public:
    Pelouse();
    void draw();
    void setTexture();
    GLuint getPelouse();
    ~Pelouse();
private:
    GLuint pelouse_;
    GLuint texturePelouse1_;
    GLuint texturePelouse2_;
    GLuint texturePelouse3_;
    GLuint texturePelouse4_;
    GLuint texturePelouse5_;


    float terrain[1000][1000];

};
#endif // PELOUSE_H
