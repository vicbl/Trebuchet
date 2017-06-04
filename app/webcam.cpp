#include "webcam.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <QDebug>
#include "math.h"
using namespace cv;
using namespace std;
Webcam::Webcam()
{

}
void Webcam::runWebCam(){

    // Variables initial of matching template
    int xInit = 250;
    int yInit = 330;
    int xPrev=xInit;
    int yPrev=yInit;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
        //return -1;
    }

    int frameWidth=cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frameHeight=cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    //cout<<"width:"<<frameWidth<<endl;
    //cout<<"height:"<<frameHeight<<endl;
    cout<<"Set size to "<<frameWidth<<"x"<<frameHeight<<endl;
    cap.set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);


    // Init the display window
    namedWindow("WebCam",1);
   // namedWindow("Template image",1);

    // Definition of the template rectangle
    int templateWidth=128;
    int templateHeight=128;
    Rect templateRect((frameWidth-templateWidth)/2,2*(frameHeight-templateHeight)/3,templateWidth,templateHeight);

    // Acquisition of the template image
    Mat templateImage; // template Mat
    Mat frame;         // frame Mat


    // Create the matchTemplate image result
    Mat resultImage;    // to store the matchTemplate result
    int result_cols =  frame.cols - templateImage.cols + 1;
    int result_rows = frame.rows - templateImage.rows + 1;
    resultImage.create( result_cols, result_rows, CV_32FC1 );
    Rect resultRect;    // to store the location of the matched rect


    //Variables qui permettent de récupérer les coordonnées de 2 templates
    double xTemp=0;
    double yTemp=0;
    double xTemp2=20;
    double yTemp2=20;


    bool templateOk=false;      // Si 50 images de suite avec la même template passe a true
    int counterOk=0;            // Permet de compter le nombre d'image où on a la même template
    int counterBloque=0;        // Permet de détecter si on est bloqué
    int counterDetection=0;     // Permet de compter le nombre d'image ou le template reconnu se déplace vers le bas

    ordreFermer_=false;
    while (waitKey(5)<0 && !ordreFermer_)
    {
        if (cap.read(frame)) // get a new frame from camera
        {

            // Si trop de difference on change la template
            if(fabs(xTemp-xTemp2)>10 && fabs(yTemp-yTemp2)>10 && !templateOk){
                counterOk=0;
                counterDetection=0;

                // vertical flip of the image
                flip(frame,frame,1);
                templateImage=Mat(frame,templateRect).clone();
                // Do the Matching between the frame and the templateImage
                matchTemplate( frame, templateImage, resultImage, TM_CCORR_NORMED );

                // Localize the best match with minMaxLoc
                double minVal; double maxVal; Point minLoc; Point maxLoc;
                minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

                // Show image
            //    imshow("Template image", templateImage);


                //si on reste bloqué
                counterBloque++;
                if (counterBloque>10){
                    qDebug()<<"Déblocage";
                    xTemp=maxLoc.x;
                    yTemp=maxLoc.y;

                }
                xTemp2=maxLoc.x;
                yTemp2=maxLoc.y;
            }else{
                counterBloque=0;
                counterOk++;
                if (counterOk>50){
                    templateOk=true;
                }

                flip(frame,frame,1);
                // Do the Matching between the frame and the templateImage
                matchTemplate( frame, templateImage, resultImage, TM_CCORR_NORMED );

                // Localize the best match with minMaxLoc
                double minValb; double maxValb; Point minLocb; Point maxLocb;
                minMaxLoc( resultImage, &minValb, &maxValb, &minLocb, &maxLocb, Mat() );
                // Save the location of the matched rect
                resultRect=Rect(maxLocb.x,maxLocb.y,templateWidth,templateHeight);


                //qDebug()<<"xTemp = "<<xTemp<<" yTemp = "<<yTemp;
                //qDebug()<<"maxLocx = "<<maxLocb.x<<" maxLocy = "<<maxLocb.y;


                // on verifie que l'objet détecté descends
                if(fabs(xTemp-maxLocb.x)<10 && (maxLocb.y)>yTemp){
                    counterDetection++;
                }
                xTemp=maxLocb.x;
                yTemp=maxLocb.y;
            }
            //*****Si pour 30 image de suite l'objet détecté descend on active la détection
            if (templateOk==false){
                rectangle(frame,templateRect,Scalar( 0, 0, 255),2,8,0);
            }
            else if(counterDetection<30) {
                rectangle(frame,resultRect,Scalar( 255, 255, 0),2,8,0);
                setxPostion(xTemp);
                setyPostion(yTemp);
            }else{
                //Modifier position trebuchet
                active_ = true;

                /*
                 * pour une webcam 640x480
                 * x -> 510
                 * y -> 350
                 *
                 */
                if (fabs(xTemp-xPrev)<40){ // si trop grand décalage en x on modifie pas la position
                    rectangle(frame,resultRect,Scalar( 0, 255, 0),2,8,0);
                    //Modifier position trebuchet

                    setxPostion(xTemp);
                    setyPostion(yTemp);
                    if (xPrev && yPrev && yPosition_-yPrev>50 && ordreLancer_ == false)
                    {
                        ordreLancer_ = true;
                        xPrev=xInit;
                        yPrev=yInit;
                    }

                    if (xPosition_>500 && yPosition_>330)
                    {
                        active_ = false;
                        ordreFermer_=true;
                        cap.release();
                        resultImage.release();
                        templateImage.release();
                    }
                    xPrev = xPosition_;
                    yPrev = yPosition_;
                }else{
                      rectangle(frame,resultRect,Scalar( 0, 255, 255),2,8,0);
                }

            }

            imshow("WebCam", frame);
        }
    }
    cvDestroyWindow("WebCam");

}


int Webcam::getxPosition(){
    return xPosition_;
}
int Webcam::getyPosition(){
    return yPosition_;
}
bool Webcam::getOrdreLancer(){
    return ordreLancer_;
}
void Webcam::setOrdreLancer(bool ol){
    ordreLancer_=ol;
}
void Webcam::setxPostion(int x){
    xPosition_=x;
}
void Webcam::setyPostion(int y){
    yPosition_=y;
}

bool Webcam::getActive(){
    return active_;
}

void Webcam::setOrdreFermer(bool fermer){
    ordreFermer_=fermer;
}
