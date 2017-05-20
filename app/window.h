// window.h

#ifndef WINDOW_H
#define WINDOW_H

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
    void on_Webcam_clicked();
    void on_jouer_clicked();

private slots:

private:
    Ui::Window *ui;



};

#endif // WINDOW_H
