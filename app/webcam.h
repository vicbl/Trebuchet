#ifndef WEBCAM_H
#define WEBCAM_H

#include <iostream>

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
private:
    int xPosition_=0;
    int yPosition_=0;
    bool active_=false;
};

#endif // WEBCAM_H
