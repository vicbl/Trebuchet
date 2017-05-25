#ifndef LOGOTELECOM_H
#define LOGOTELECOM_H

#include <GL/glu.h>
class LogoTelecom
{
public:
    LogoTelecom();
    void draw();
    void setTexture();
    void drawPartUJM();
    void drawPartTSE();
    GLuint getCompleteLogoTelecom();
    ~LogoTelecom();
private:
    GLuint logoTelecom_;
    GLuint logoUJM_;
    GLuint textureBois_;
    GLuint textureTSE_;
    GLuint textureUJM_;
    GLuint completeLogoTelecom_;
    GLuint boxBois;
};

#endif // LOGOTELECOM_H
