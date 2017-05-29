#ifndef TREBUCHET_H
#define TREBUCHET_H
#include "box.h"

#include <GL/glu.h>
class Trebuchet
{
public:
    Trebuchet();
    GLuint draw(GLuint corde,int levierRotation);
    void setTexture();
    ~Trebuchet();
private:
    GLuint textureBois_;
    GLuint textureLevier_;
    GLuint completeTrebuchet_;
    GLuint textureContrePoids_;
};
#endif // TREBUCHET_H
