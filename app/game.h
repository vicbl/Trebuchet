#ifndef GAME_H
#define GAME_H


class Game
{
public:
    Game(int difficulty);
    int getCiblePositionX();
    int getCiblePositionY();
    int getDistanceTrebuchet();
    void newPostion();
private:

    int difficulty_;
    int distanceTrebuchet_;
    int ciblePositionX_;
    int ciblePositionY_;
};

#endif // GAME_H
