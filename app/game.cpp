#include "game.h"
#include <cstdlib>
Game::Game(int difficulty)
{
    this->difficulty_=difficulty;

}

void Game::newPostion(){
    int max;
    int min;

    /*
    switch(difficulty_){
    case 1  :
        max=2;
        min=-2;
        ciblePositionX_ = rand() % (max-min + 1) + min;   // x in the range 0 to 10
        ciblePositionY_ = rand() % (max-min + 1) + min;   // y in the range 0 to 10
        distanceTrebuchet_=32;
        break;
    case 2  :
        max=3;
        min=-3;
        ciblePositionX_ = rand() % (max-min + 1) + min;   // x in the range 0 to 10
        ciblePositionY_ = rand() % (max-min + 1) + min;   // y in the range 0 to 10
        distanceTrebuchet_=14;
        break;

    case 3  :
        max=4;
        min=-4;
        ciblePositionX_ = rand() % (max-min + 1) + min;   // x in the range 0 to 10
        ciblePositionY_ = rand() % (max-min + 1) + min;   // y in the range 0 to 10
        distanceTrebuchet_=16;
        break;
    case 4  :
        max=5;
        min=-5;
        ciblePositionX_ = rand() % (max-min + 1) + min;   // x in the range 0 to 10
        ciblePositionY_ = rand() % (max-min + 1) + min;   // y in the range 0 to 10
        distanceTrebuchet_=18;
        break;
    case 5  :
        max=6;
        min=-6;
        ciblePositionX_ = rand() % (max-min + 1) + min;   // x in the range 0 to 10
        ciblePositionY_ = rand() % (max-min + 1) + min;   // y in the range 0 to 10
        distanceTrebuchet_=75;
        break;
    default :
        max=1;
        min=-1;
        ciblePositionX_ = rand() % (max-min + 1) + min;   // x in the range 0 to 10
        ciblePositionY_ = rand() % (max-min + 1) + min;   // y in the range 0 to 10
        distanceTrebuchet_=10;
    }

    */


    max=difficulty_+1;
    min=-(difficulty_+1);
    ciblePositionX_ = rand() % (max-min + 1) + min;   // x in the range 0 to 10
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

int Game::getDistanceTrebuchet(){
    return distanceTrebuchet_;
}
