#include "game.h"
#include <cstdlib>
#include <QDebug>
#include <cmath>
#include"math.h"
#define PI 3.14159265
Game::Game(int difficulty)
{
    this->nbTotalCibleTouchee_=0;
    this->difficulty_=difficulty;
    this->score_=0;
}

void Game::newPostion(){
    int max;
    int min;

    // Difficulty : 1-5

    firstPassage_=true;
    cibleTouchee_=false;
    max=difficulty_+1;
    min=-(difficulty_+1);
    ciblePositionX_ = rand() % 3*((max-min) + 1) + 3*min;   // x in the range 0 to 10
    ciblePositionY_ = rand() % (max-min + 1) + min;   // y in the range 0 to 10
    distanceTrebuchet_=22+14*difficulty_;   // Cibles générées entre : [[34/38] - [86-98]
    // Lancer possible du trébuchet: [33 - 102]

}

int Game::getCiblePositionX(){
    return ciblePositionX_;
}
int Game::getCiblePositionY(){
    return ciblePositionY_;
}

bool Game::getCibleTouchee(){
    return cibleTouchee_;
}
int Game::getDistanceTrebuchet(){
    return distanceTrebuchet_;
}
int Game::getScore(){
    return score_;
}
int Game::getNbTotalCibleTouchee(){
    return nbTotalCibleTouchee_;
}

int Game::calculScore(float xPosBoulet, float zPosBoulet){

    float distanceCible=sqrt(pow((distanceTrebuchet_+ciblePositionY_),2)+pow(ciblePositionX_,2));
    xPosBoulet=xPosBoulet-(distanceCible+1.7)+1.22;
    /*qDebug()<<"xboulet = "<<xPosBoulet;
    qDebug()<<"yboulet = "<<distanceCible;
    qDebug()<<"zboulet = "<<zPosBoulet<< "yBouletZone cible = "<<zPosBoulet;*/




    /* float distance=10;
    int angle =100;
    float xBoulet= sin((180-angle)*PI/180)*distance;
    float yBoulet= cos((180-angle)*PI/180)*distance;
    /*qDebug()<<"Distance ="<<distance<<" Angle ="<<angle;
    qDebug()<<"Y théorique"<<yBoulet<<"xreel="<<(distanceTrebuchet_+ciblePositionY_);
    qDebug()<<"X théorique"<<xBoulet<<"yreel="<<ciblePositionX_;


    float yZoneCible=distanceTrebuchet_+ciblePositionY_-yBoulet;

    float xZoneCible=ciblePositionX_-xBoulet;

    //  qDebug()<<"xZoneCible"<<xZoneCible<<"    yZoneCible"<<yZoneCible;


    if(fabs(xZoneCible)<1 && fabs(yZoneCible)<1 && firstPassage_){


        if(fabs(xZoneCible)<0.1 && fabs(yZoneCible)<0.1){
            score_=score_+10;
        }else if (fabs(xZoneCible)<0.2 && fabs(yZoneCible)<0.2) {
            score_=score_+9;
        }else if (fabs(xZoneCible)<0.3 && fabs(yZoneCible)<0.3) {
            score_=score_+8;
        }else if (fabs(xZoneCible)<0.4 && fabs(yZoneCible)<0.4) {
            score_=score_+7;
        }else if (fabs(xZoneCible)<0.5 && fabs(yZoneCible)<0.5) {
            score_=score_+6;
        }else if (fabs(xZoneCible)<0.6 && fabs(yZoneCible)<0.6) {
            score_=score_+5;
        }else if (fabs(xZoneCible)<0.7 && fabs(yZoneCible)<0.7) {
            score_=score_+4;
        }else if (fabs(xZoneCible)<0.8 && fabs(yZoneCible)<0.8) {
            score_=score_+3;
        }else if (fabs(xZoneCible)<0.9 && fabs(yZoneCible)<0.9) {
            score_=score_+2;
        }else{
            score_++;
        }
        qDebug()<<"*********************Cible touchée, votre score est : "<<score_<<"*****************************";
        nbTotalCibleTouchee_++;
        cibleTouchee_=true;
        firstPassage_=false;
    }*/
    //  qDebug()<<"zboulet = "<<zPosBoulet;



    if (zPosBoulet<0.65){
        if (xPosBoulet<0.1 && xPosBoulet>-0.1) {
            score_=score_+10;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        }
        else if (xPosBoulet<0.2 && xPosBoulet>-0.2) {
            score_=score_+9;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;

        } else if (xPosBoulet<0.3 && xPosBoulet>-0.3) {
            score_=score_+8;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<0.4 && xPosBoulet>-0.4) {
            score_=score_+7;
            cibleTouchee_=true;
        } else if (xPosBoulet<0.5 && xPosBoulet>-0.5) {
            score_=score_+6;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<0.6 && xPosBoulet>-0.6) {
            score_=score_+5;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<0.7 && xPosBoulet>-0.7) {
            score_=score_+4;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<0.8 && xPosBoulet>-0.8) {
            score_=score_+3;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        }else if(xPosBoulet<0.9&&xPosBoulet>-0.9){
            score_=score_+2;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        }else if(xPosBoulet<1&&xPosBoulet>-1){
            score_=score_+1;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        }
    }

}






