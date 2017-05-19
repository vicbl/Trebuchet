#ifndef GRID_H
#define GRID_H

#include <GL/glu.h>

class Grid
{
public:
    Grid(int nbLines,int nbColumns, double width);
    GLuint getCompleteGrid();
    ~Grid();
private:
    void draw();
    void drawGridPart();

    double width_;//width of the grid between 0 and 1
    int nbLines_;
    int nbColumns_;
    GLuint completeGrid_;
    GLuint gridPart_;
};

#endif // GRID_H
