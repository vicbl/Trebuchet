#ifndef WEBCAM_H
#define WEBCAM_H

#include <iostream>
#include <QDebug>
#include <QtWidgets>

class Webcam
{


public:
    Webcam();
    int getxPosition();
    int getyPosition();
    bool getActive();
    void runWebCam();
    void setxPostion(int x);
    void setyPostion(int y);
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    int xPosition_=0;
    int yPosition_=0;
    bool active_=false;
    bool firstPassage_=true;
    bool ordreFermer_ = false;
};

#endif // WEBCAM_H
