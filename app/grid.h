#ifndef GRID_H
#define GRID_H

#include <GL/glu.h>

class Grid
{
private:
    void drawGridPart();
    double width_;//width of the grid between 0 and 1
    int nbLines_;
    int nbColumns_;
    GLuint completeGrid_;
    GLuint gridPart_;

public:
    Grid(int nbLines,int nbColumns, double width);
    void draw();
    GLuint getCompleteGrid();
    ~Grid();
};

#endif // GRID_H
