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
    GLuint texturePelouse_;

};
#endif // PELOUSE_H
