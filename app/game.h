#ifndef GAME_H
#define GAME_H

/* classe : game
 * Ecrite par Victor Blanchard,
 * Diverses améliorations par Louis Berger et Victor Blanchard
 * Gère le déroulement de la partie,
 * Détermine si le boulet touche la cible
 * Calcul le score en conséquence
 * Envoie le signal de fin de partie
 * Compte le nombre de cible touchées et le nombre de cibles restantes
 */

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
    bool cibleTouchee_=false;
    bool firstPassage_=true;

public:
    Game(int difficulty);
    int getCiblePositionX();
    int getCiblePositionY();
    int getDistanceTrebuchet();
    int getNbTotalCibleTouchee();
    bool getCibleTouchee();
    int getScore();
    void newPostion();
    int calculScore(float xPosBoulet, float zPosBoulet);

};

#endif // GAME_H
