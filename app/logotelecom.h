#ifndef LOGOTELECOM_H
#define LOGOTELECOM_H

#include <GL/glu.h>
class LogoTelecom
{
public:
    LogoTelecom();
    GLuint draw();
    void setTexture();
    void drawPartUJM();
    void drawPartTSE();
    GLuint getCompleteLogoTelecom();
    ~LogoTelecom();
private:
    GLuint logoTelecom_;
    GLuint logoUJM_;
    GLuint texture_[];
    GLuint completeLogoTelecom_;

};

#endif // LOGOTELECOM_H
