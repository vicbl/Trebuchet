#ifndef SAVE_H
#define SAVE_H

#include<QString>

class Save
{
private:
    QString fileName_;

public:
    Save(QString fileName);
    void saveBest(int score, int difficulty, QString playerName);
    QString getBestName(int difficulty);
    int getBestScore(int difficulty);
};

#endif // SAVE_H
