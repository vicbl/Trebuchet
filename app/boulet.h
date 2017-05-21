#ifndef BOULET_H
#define BOULET_H

#include <GL/glu.h>

class Boulet
{
private:
    GLfloat coord_y = 7; // hauteur
    GLfloat coord_x = 1.7; // distance au trébuchet
    int v0 = 0;
    int axe = 180;
    float t = 0;
    bool finTrajectoire = false;
    GLuint boulet;

public:
    Boulet();

    GLuint draw();
    void reset();

    void set_v0(float v);
    void set_axe(int a);
    void set_x(float x);
    void set_y(float y);

    float get_x();
    float get_y();
    bool getFin();

};

#endif // BOULET_H
