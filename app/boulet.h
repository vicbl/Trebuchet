//boulet.h

#ifndef BOULET_H
#define BOULET_H

/** classe : Boulet
 * Ecrite par Louis Berger,
 * Diverses améliorations par Louis Berger et Victor Blanchard
 * Gère la trajectoire du boulet après son lancer
 * Crée une liste affichant le boulet lors de sa course et après son atterissage
 */


#include <GL/glu.h>
#include "textures.h"
#include "game.h"
class Boulet
{
private:
    GLfloat coordY_= 10.8; // hauteur
    GLfloat coordX_ = 2.4; // distance au trébuchet
    float v0_;
    int axe_ = 180;
    float t_ = 0;
    bool finTrajectoire_ = false;
    GLuint boulet_;
    GLuint texturePierre_;
    bool cibleTouchee_=false;

public:
    Boulet();
    void setTexture(Textures tex);
    GLuint draw(Game * game_, bool slowMode);
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
