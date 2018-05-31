//#########################
//Pekka Kana QT Sprite Creator - main.cpp
//by Danilo Lemos 2017
//#########################

#include "sc_window.h"
#include <QApplication>
#include <data_window.h>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    SC_Window w;
    Data_Window data;

    w.data_window = &data;
    w.show();

    return a.exec();
}
