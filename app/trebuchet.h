#ifndef TREBUCHET_H
#define TREBUCHET_H
#include "box.h"
#include "textures.h"
#include <GL/glu.h>
class Trebuchet
{
private:
    GLuint textureBois_;
    GLuint texturePierre_;
    GLuint textureLevier_;
    GLuint textureContrePoids_;
    GLuint completeTrebuchet_;

public:
    Trebuchet();
    GLuint draw(GLuint corde,int levierRotation);
    void setTexture(Textures tex);
    ~Trebuchet();

};
#endif // TREBUCHET_H
