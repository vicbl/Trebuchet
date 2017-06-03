#ifndef LIGHTING_H
#define LIGHTING_H



#include <GL/glu.h>
#include"box.h"
class Lighting
{
public:
    Lighting();
    void setTexture();
    void draw();
    GLuint getCompleteLighting();
    ~Lighting();
private:

    GLuint lighting_;
    GLuint textureCiment_;
    GLuint textureProjecteur_;
};

#endif // LIGHTING_H
