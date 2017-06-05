#ifndef BOX_H
#define BOX_H

/* classe : Box
 * Ecrite par Victor Blanchard,
 * Crée une liste affichant une boite de dimension :
 * width*height*thickness
 * Et de texture : texture
 */

#include <GL/glu.h>
class Box
{
private:
    void draw();
    double width_;
    double height_;
    double thickness_;
    GLuint texture_;
    GLuint completeBox_;

public:
    Box(double width, double height, double thickness, GLuint texture);
    GLuint getCompleteBox();
    ~Box();
};


#endif // BOX_H
