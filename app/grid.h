//grid.h

#ifndef GRID_H
#define GRID_H

/** classe : Grid
 * Ecrite par Victor Blanchard,
 * Génère une liste d'affichage du grillage de protection
 */

#include <GL/glu.h>
#include "textures.h"

class Grid
{
private:
    void drawGridPart();
    double width_; //epaisseur du grillage entre 0 et 1
    int nbLines_;
    int nbColumns_;
    GLuint texturePilier_;
    GLuint gridPart_;
    GLuint pilier_;
    GLuint completeGrid_; // List contenant le grillage former des pilier et d'une grille de nbLines_ et nbColumns



public:
    Grid(int nbLines,int nbColumns, double width);
    void draw();
    void setTexture(Textures tex);
    GLuint getCompleteGrid();
    ~Grid();
};

#endif // GRID_H
