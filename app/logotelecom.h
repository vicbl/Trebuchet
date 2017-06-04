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
    void drawPartUJM();
    void drawPartTSE();

public:
    LogoTelecom();
    void draw();
    void setTexture(Textures tex);
    GLuint getCompleteLogoTelecom();
    ~LogoTelecom();

};

#endif // LOGOTELECOM_H
