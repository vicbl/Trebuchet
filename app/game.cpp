#include "game.h"
#include <cstdlib>
#include <QDebug>
#include <cmath>
#define PI 3.14159265
Game::Game(int difficulty, QString name)
{
    this->nbTotalCibleTouchee_=0;
    this->difficulty_=difficulty;
    this->name_=name;
    this->score_=0;
}

void Game::newPostion(){
    int max;
    int min;


    firstPassage_=true;
    cibleTouchee_=false;
    max=difficulty_+1;
    min=-(difficulty_+1);
    ciblePositionX_ = rand() % 3*((max-min) + 1) + 3*min;   // x in the range 0 to 10
    ciblePositionY_ = rand() % (max-min + 1) + min;   // y in the range 0 to 10
    distanceTrebuchet_=22+10*difficulty_;   // Cibles générées entre : [[30/34] - [66-78]
    // Lancer possible du trébuchet: [29 - 80]

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

int Game::calculScore(float distance, float angle){

    float xBoulet= sin((180-angle)*PI/180)*distance;
    float yBoulet= cos((180-angle)*PI/180)*distance;
    /*qDebug()<<"Distance ="<<distance<<" Angle ="<<angle;
    qDebug()<<"Y théorique"<<yBoulet<<"xreel="<<(distanceTrebuchet_+ciblePositionY_);
    qDebug()<<"X théorique"<<xBoulet<<"yreel="<<ciblePositionX_;*/


    float yZoneCible=distanceTrebuchet_+ciblePositionY_-yBoulet;

    float xZoneCible=ciblePositionX_-xBoulet;

   // qDebug()<<"xZoneCible"<<xZoneCible<<"    yZoneCible"<<yZoneCible;

    if(abs(xZoneCible)<5 && abs(yZoneCible)<5 && firstPassage_){
        score_++;
        qDebug()<<"*********************Cible touchée, votre score est : "<<score_<<"*****************************";

        nbTotalCibleTouchee_++;
        cibleTouchee_=true;
        firstPassage_=false;
    }


}


