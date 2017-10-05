//#########################
//Pekka Kana QT Sprite Creator - sc_window.cpp
//by Danilo Lemos 2017
//#########################

#include <QFileDialog>
#include <QPixmap>
#include <unistd.h>
#include "sc_window.h"
#include "ui_sc_window.h"

#include "../src/pistedraw.h"
#include "../src/platform.h"

SC_Window::SC_Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::SC_Window){
    ui->setupUi(this);
    sprite_prototype = new PK2Sprite_Prototyyppi;
    sprite_prototype->Uusi();

    QPixmap* pixmap = PisteDraw2_Start(150,150);
    ui->frame->setPixmap(*pixmap);

    char op[] = "SSSS";
    if(ui->frame->pixmap() == 0) op[2] = 'A';
    ui->lab_sound->setText(op);
}

SC_Window::~SC_Window(){
    delete ui;
}

//Slots
void SC_Window::open(){
    this->filename = QFileDialog::getOpenFileName(this,"Selecione um sprite.", "", "Sprites (*.spr)");

#ifdef _WIN32
    char sep = '\\';
#else
    char sep = '/';
#endif

    char path[_MAX_PATH] = "";
    QByteArray bap = filename.toLatin1(); //Path
    QByteArray baf = bap; //File


    bap.data()[bap.lastIndexOf(sep)+1] = '\0';
    baf.remove(0,bap.lastIndexOf('\0'));
    chdir(bap.data());

    sprite_prototype->Lataa(bap.data(),baf.data());

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
