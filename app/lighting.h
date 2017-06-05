#ifndef LIGHTING_H
#define LIGHTING_H

/* classe : Lighting
 * Ecrite par Victor Blanchard,
 * Génère une liste d'affichage d'un projecteur
 */

#include <GL/glu.h>
#include"box.h"
#include "textures.h"

class Lighting
{
private:
    GLuint lighting_;
    GLuint textureCiment_;
    GLuint textureProjecteur_;

public:
    Lighting();
    void setTexture(Textures tex);
    void draw();
    GLuint getCompleteLighting();
    ~Lighting();

};

#endif // LIGHTING_H
