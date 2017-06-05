// window.h

#ifndef WINDOW_H
#define WINDOW_H


/* classe : Window
 * Ecrite par Victor Blanchard et Louis Berger
 * Génère l'interface graphique
 * Associe les action sur chaque bouton aux fonctions correspondante dans myGlWidget
 * Associe les demande d'affichage de myGlWidget aux label de l'interface
 * Gère les différents appuie sur les touches et le associe aux fonctions correspondantes de myGlWidget:
 * A : zoom arrière
 * E : zoom avant
 * Z : rotation + autour de xScene (angle de vue de plongée)
 * S : rotation - autour de xScene (angle de vue de plongée)
 * Q : rotation horaire autour de zScene (angle de vue latérale)
 * D : rotation trigonométrique autour de zScene (angle de vue latérale)
 * C : Recentrage derrière le trébuchet
 */

#include <QWidget>
#include <QSlider>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void on_lancerBouton_clicked();
    void on_startButton_clicked();
    void on_vueSuivie_stateChanged();
    void on_trajectory_stateChanged();
    void on_nightMode_stateChanged();

private slots:
    void on_forceSlider_valueChanged(int value);

private:
    Ui::Window *ui;

};

#endif // WINDOW_H
