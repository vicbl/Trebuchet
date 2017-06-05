//save.h

#ifndef SAVE_H
#define SAVE_H

/** classe : Save
 * Ecrite par Victor Blanchard
 * Sauvegarde les scores dans le fichier fileName
 * Permet de modifier et d'afficher les meilleurs scores
 */

#include<QString>

class Save
{
private:
    QString fileName_;

public:
    Save(QString fileName);
    void saveBest(int score, int difficulty, QString playerName); //On sauvegarde le score à la fin de la partie dans un fichier texte
    QString getBestName(int difficulty);
    int getBestScore(int difficulty);
};

#endif // SAVE_H
