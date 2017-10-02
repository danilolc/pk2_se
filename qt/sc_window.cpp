//#########################
//Pekka Kana QT Sprite Creator - sc_window.cpp
//by Danilo Lemos 2017
//#########################

#include <QFileDialog>
#include "sc_window.h"
#include "ui_sc_window.h"

#include "../src/platform.h"

SC_Window::SC_Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::SC_Window){
    ui->setupUi(this);
    sprite_prototype = new PK2Sprite_Prototyyppi;
    sprite_prototype->Uusi();
}

SC_Window::~SC_Window(){
    delete ui;
}


//Slots
void SC_Window::open(){
    this->filename = QFileDialog::getOpenFileName(this,"Selecione um sprite.", "", "Sprites (*.spr)");

    char path[_MAX_PATH] = "";
    QByteArray ba = filename.toLatin1();
    sprite_prototype->Lataa(path,ba.data());

    this->update();
}
void SC_Window::save(){

}
void SC_Window::reset(){

}


//Internal Functions
void SC_Window::update(){
    ui->lab_sound->setText(sprite_prototype->aanitiedostot[0]);
}
