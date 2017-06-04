#ifndef LOGOTELECOM_H
#define LOGOTELECOM_H

#include <GL/glu.h>
#include "textures.h"
class LogoTelecom
{
private:
    GLuint logoTelecom_;
    GLuint logoUJM_;
    GLuint textureBois_;
    GLuint textureTSE_;
    GLuint textureUJM_;
    GLuint completeLogoTelecom_;
    GLuint boxBois;


public:
    LogoTelecom();
    void draw();
    void setTexture(Textures tex);
    void drawPartUJM();
    void drawPartTSE();
    GLuint getCompleteLogoTelecom();
    ~LogoTelecom();

};

#endif // LOGOTELECOM_H
