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
    GLuint getCompleteTrebuchet();
    ~Trebuchet();
private:
    GLuint texture_[];
    GLuint completeTrebuchet_;

};
#endif // TREBUCHET_H
