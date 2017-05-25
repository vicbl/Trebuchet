#ifndef CIBLE_H
#define CIBLE_H


#include "box.h"

#include <GL/glu.h>
class Cible
{
public:
    Cible();
    void draw();
    void setTexture();
    void drawPart();
    GLuint getCompleteCible();
    ~Cible();
private:
    GLuint cible_;
    GLuint textureBois_;
    GLuint textureCible_;
    GLuint completeCible_;

};

#endif // CIBLE_H
