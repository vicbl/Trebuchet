#ifndef WEBCAM_H
#define WEBCAM_H

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
