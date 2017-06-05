//cible.h

#ifndef CIBLE_H
#define CIBLE_H


/** classe : Cible
 * Ecrite par Victor Blanchard
 * Crée une liste affichant une cible (texture)
 * avec deux pieds en bois
 */

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
