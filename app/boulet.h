#ifndef BOULET_H
#define BOULET_H

#include <GL/glu.h>
#include "textures.h"
#include "game.h"
class Boulet
{
private:
    GLfloat coord_y = 7.1; // hauteur
    GLfloat coord_x = 1.7; // distance au trébuchet
    float v0;
    int axe = 180;
    float t = 0;
    bool finTrajectoire = false;
    GLuint boulet;
    GLuint texturePierre_;
    bool cibleTouchee_=false;

public:
    Boulet();
    void setTexture(Textures tex);
    GLuint draw(Game * game_);
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
