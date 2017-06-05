#ifndef GRID_H
#define GRID_H

/* classe : Grid
 * Ecrite par Victor Blanchard,
 * Génère une liste d'affichage du grillage de protection
 */

#include <GL/glu.h>
#include "textures.h"

class Grid
{
private:
    void drawGridPart();
    double width_;//width of the grid between 0 and 1
    int nbLines_;
    int nbColumns_;
    GLuint texturePilier_;
    GLuint gridPart_;
    GLuint pilier_;
    GLuint completeGrid_;



public:
    Grid(int nbLines,int nbColumns, double width);
    void draw();
    void setTexture(Textures tex);
    GLuint getCompleteGrid();
    ~Grid();
};

#endif // GRID_H
