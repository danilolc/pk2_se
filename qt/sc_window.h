//#########################
//Pekka Kana QT Sprite Creator - sc_window.cpp
//by Danilo Lemos 2017
//#########################

#ifndef SC_WINDOW_H
#define SC_WINDOW_H

#include <QMainWindow>
#include <QThread>
#include "../src/sprite.h"

namespace Ui {
class SC_Window;
}

class SC_Window : public QMainWindow{
    Q_OBJECT

public:
    explicit SC_Window(QWidget *parent = 0);
    ~SC_Window();
    void animate();

    bool animating = false;

public slots:
    void open();
    void save();
    void reset();

    void boxframe_changed(int value);
    void boxcolor_changed(int value);
    void boxanimate_changed(int value);

    void restartanimation();



private:
    Ui::SC_Window *ui;
    QString filename;
    PK2Sprite_Prototyyppi* sprite_prototype;
    PK2Sprite* sprite;

    int currentframe = 0;

    void LinkSignals();
    void updateAll();
};

class AnimThread : public QThread {
    Q_OBJECT
    void run();
public:
    SC_Window* window;
    bool active;
};

#endif // SC_WINDOW_H
