#ifndef SAVE_H
#define SAVE_H

#include<QString>

class Save
{
public:
    Save(QString filename);
    void saveBest(int score, int difficulty, QString playerName);
    QString getBestName(int difficulty);
    int getBestScore(int difficulty);

private:
    QString filename_;
};

#endif // SAVE_H
