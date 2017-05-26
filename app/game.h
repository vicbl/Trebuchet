#ifndef GAME_H
#define GAME_H

#include <QString>
class Game
{
public:
    Game(int difficulty, QString name);
    int getCiblePositionX();
    int getCiblePositionY();
    int getDistanceTrebuchet();
    int getNbTotalCible();
    int getBestScore();
    bool getCibleTouchee();
    int getScore();
    void newPostion();
    int calculScore(float distance, float angle);

private:
    int nbTotalCible_; // Nombre de cibles touchées
    int difficulty_;
    int distanceTrebuchet_;
    int ciblePositionX_;
    int ciblePositionY_;
    int score_;
    int bestScore_[3];
    QString name_;
    bool cibleTouchee_=false;
    bool firstPassage_=true;

};

#endif // GAME_H
