//webcam.h

#ifndef WEBCAM_H
#define WEBCAM_H


/** classe : Webcam
 * Ecrite par Victor Blanchard et Louis Berger
 * Génère une fenêtre d'acquisition de la webcam
 * Gère la position de la main et envoie des données en conséquence
 * Fermeture de la fenêtre lors du placement de la main en bas à droite de l'écran
 * Rectangle rouge: acquisition
 * Rectagle turquoise: demande de validation de la main
 * (actif lorsque la main reste plus de 50 image d'affilé sur le ractangle rouge)
 * Si abaissement de la main détectée dans le rectangle turquoise: main validée
 * Rectangle vert: main validée, attente des ordres
 * Rectangle jaune: erreur de détection: replacer la main à la position précédente
 * Ordre:
 * Déplacement latéral = orientation du trébuchet (axe)
 * Déplacement vertical modéré = puissance du lancer (force)
 * Déplacement vertical rapide = ordre de lancer
 * Main en bas à droite de l'écran = ordre de fermeture
 *
 */

#include <iostream>
#include <QDebug>
#include <QtWidgets>
#include <QWidget>
class Webcam
{
private:
    int xPosition_=0;
    int yPosition_=0;
    bool detection_=false;
    bool active_=false;
    bool ordreLancer_=false;
    bool ordreFermer_ = false;

public:
    Webcam();
    int getxPosition();
    int getyPosition();
    bool getOrdreLancer();
    void setOrdreLancer(bool ol);
    bool getActive();
    void runWebCam();
    void setxPostion(int x);
    void setyPostion(int y);

    void setOrdreFermer(bool fermer);

};

#endif // WEBCAM_H
