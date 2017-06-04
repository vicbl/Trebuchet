#ifndef CIBLE_H
#define CIBLE_H

#include "box.h"
#include "textures.h"

#include <GL/glu.h>
class Cible
{
private:
    GLuint cible_;
    GLuint textureBois_;
    GLuint textureCible_;
    GLuint completeCible_;

public:
    Cible();
    void draw();
    void setTexture(Textures tex);
    void drawPart();
    GLuint getCompleteCible();
    ~Cible();
};

#endif // CIBLE_H
