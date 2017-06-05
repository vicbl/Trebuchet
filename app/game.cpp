#include "game.h"
#include <cstdlib>
#include <QDebug>
#include <cmath>
#include "math.h"

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

void Game::calculScore(float xPosBoulet, float zPosBoulet){

    float distanceCible=sqrt(pow((distanceTrebuchet_+ciblePositionY_),2)+pow(ciblePositionX_,2))+1.8;
    //qDebug() << "xBoulet = " << xPosBoulet << " xCible = " << distanceCible;


    xPosBoulet=distanceCible-xPosBoulet;
 


    if (zPosBoulet<1){

        if (xPosBoulet<.4 && xPosBoulet>.4) {
            score_=score_+10;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<.6 && xPosBoulet>-.6) {
            score_=score_+9;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<.9 && xPosBoulet>-.9) {
            score_=score_+8;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<1.2 && xPosBoulet>-1.2) {
            score_=score_+7;
            cibleTouchee_=true;
        } else if (xPosBoulet<1.5 && xPosBoulet>-1.5) {
            score_=score_+6;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<1.8 && xPosBoulet>-1.8) {
            score_=score_+5;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<2.1 && xPosBoulet>-2.1) {
            score_=score_+4;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        } else if (xPosBoulet<2.4 && xPosBoulet>-2.4) {
            score_=score_+3;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        }else if(xPosBoulet<2.7 && xPosBoulet>-2.7){
            score_=score_+2;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        }else if(xPosBoulet<3 && xPosBoulet>-3){
            score_=score_+1;
            cibleTouchee_=true;
            nbTotalCibleTouchee_++;
        }
        //qDebug() << "xBoulet = " << xPosBoulet << "zBoulet = " << zPosBoulet;
    }

}






