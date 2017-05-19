#include "webcam.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <QDebug>
using namespace cv;
using namespace std;
Webcam::Webcam()
{

}
void Webcam::runWebCam(){

    // Variables initial of matching template
    int xInit=0;
    int yInit=0;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
        //return -1;
    }

    int frameWidth=cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frameHeight=cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    cout<<"width:"<<frameWidth<<endl;
    cout<<"height:"<<frameHeight<<endl;
    frameWidth=frameWidth;
    frameHeight=frameHeight;
    cout<<"Set size to "<<frameWidth<<"x"<<frameHeight<<endl;
    cap.set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);


    // Init the display window
    namedWindow("WebCam",1);

    // Ask template image
    cout<<"Put the template image inside the red square and hit a key !"<<endl;

    // Definition of the template rectangle
    int templateWidth=128;
    int templateHeight=128;
    Rect templateRect((frameWidth-templateWidth)/2,2*(frameHeight-templateHeight)/3,templateWidth,templateHeight);

    // Acquisition of the template image
    Mat templateImage; // template Mat
    Mat frame;         // frame Mat
    while (waitKey(10)<0)
    {

        if (cap.read(frame)) // get a new frame from camera
        {

            // vertical flip of the image
            flip(frame,frame,1);
            // Copy the template rect
            templateImage=Mat(frame,templateRect).clone();
            // Draw red rectangle on the frame
            rectangle(frame,templateRect,Scalar( 0, 0, 255),2,8,0);
            // Display the frame
            imshow("WebCam", frame);
        }

    }

    // Show the template image
  /*  namedWindow("Template image",1);
    imshow("Template image", templateImage);*/

    // Create the matchTemplate image result
    Mat resultImage;    // to store the matchTemplate result
    int result_cols =  frame.cols - templateImage.cols + 1;
    int result_rows = frame.rows - templateImage.rows + 1;
    resultImage.create( result_cols, result_rows, CV_32FC1 );
    Rect resultRect;    // to store the location of the matched rect

    // Init the window to display the result
   // namedWindow("matchTemplate result",1);

    // Online template matching
    cout<<"Online template matching, hit a key to stop"<<endl;
    while (waitKey(5)<0)
    {
        if (cap.read(frame)) // get a new frame from camera
        {
            // vertical flip of the image
            flip(frame,frame,1);

            // Do the Matching between the frame and the templateImage
            matchTemplate( frame, templateImage, resultImage, TM_CCORR_NORMED );

            // Localize the best match with minMaxLoc
            double minVal; double maxVal; Point minLoc; Point maxLoc;
            minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
            // Save the location fo the matched rect
            resultRect=Rect(maxLoc.x,maxLoc.y,templateWidth,templateHeight);

            // Show the result
            Mat normResultImage;
            // Normalize values
            normalize(resultImage,normResultImage,1,0,NORM_MINMAX);
            // Return to RGB to plot the max in red
            cvtColor(normResultImage,normResultImage,CV_GRAY2RGB);
            // Draw a red square
            rectangle(normResultImage,Rect(maxLoc.x,maxLoc.y,3,3),Scalar( 0, 0, 1),2,8,0);
            if (firstPassage_==true){
                active_=true;
                firstPassage_=false;
                xInit=maxLoc.x;
                yInit=maxLoc.y;
            }
            setxPostion(maxLoc.x-xInit);
            setyPostion(maxLoc.y-yInit);

       //     qDebug()<<"xpos= "<<xPosition_<<" et ypos=  "<<yPosition_;
            // Show image
          //  imshow("matchTemplate result",normResultImage);

            // Draw green rectangle on the frame
            rectangle(frame,resultRect,Scalar( 0, 255, 0),2,8,0);
            // Display the frame
            imshow("WebCam", frame);


        }
    }
}

int Webcam::getxPosition(){
    return xPosition_;
}
int Webcam::getyPosition(){
    return yPosition_;
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
