#ifndef GAME_H
#define GAME_H

#include <QString>
class Game
{
private:
    int nbTotalCibleTouchee_; // Nombre de cibles touchées
    int difficulty_;
    int distanceTrebuchet_;
    int ciblePositionX_;
    int ciblePositionY_;
    int score_;
    int bestScore_[3];
    QString name_;
    bool cibleTouchee_=false;
    bool firstPassage_=true;

public:
    Game(int difficulty, QString name);
    int getCiblePositionX();
    int getCiblePositionY();
    int getDistanceTrebuchet();
    int getNbTotalCibleTouchee();
    int getBestScore();
    bool getCibleTouchee();
    int getScore();
    void newPostion();
    int calculScore(float xPosBoulet, float zPosBoulet);

};

#endif // GAME_H
