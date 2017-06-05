//logotelcom.h

#ifndef LOGOTELECOM_H
#define LOGOTELECOM_H

/** classe : Logotelecom
 * Ecrite par Victor Blanchard,
 * Génère une liste affichant un panneau d'affichage "Telecom Saint Etienne"
 */

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
    GLuint completeLogoTelecom_; // List contenant un panneau d'affichage
    GLuint boxBois_;
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
