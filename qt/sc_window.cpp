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
#include "../src/types.h"

const BYTE colorlist_values[] = {255, 0, 32, 64, 96, 128, 160, 192};
const char colorlist[][16] = {
    "Normal",
    "Gray",
    "Blue",
    "Red",
    "Green",
    "Orenge",
    "Violet",
    "Turquoise"
};

SC_Window::SC_Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::SC_Window){
    ui->setupUi(this);
    sprite_prototype = new PK2Sprite_Prototyyppi;
    sprite_prototype->Uusi();

    PisteDraw2_Start(ui->frame);

    char op[] = "SSSS";
    if(ui->frame->pixmap() == 0) op[2] = 'A';
    ui->lab_sound->setText(op);

    for(int i = 0; i < 8; i++)
        ui->box_color->addItem(colorlist[i]);
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

    ui->box_frame->setEnabled(true);
    ui->box_frame->setValue(0);
    ui->box_frame->setMaximum(sprite_prototype->frameja - 1);
    this->boxframe_changed(0);

    int color = sprite_prototype->vari;
    ui->box_color->setEnabled(true);
    //ui->box_color->setCurrentIndex(-1);
    for(int i = 0; i < 8; i++)
        if(colorlist_values[i] == color)
            ui->box_color->setCurrentIndex(i);


    this->update();
}
void SC_Window::save(){

}
void SC_Window::reset(){

}
void SC_Window::boxframe_changed(int value){
    currentframe = value;
    sprite_prototype->Piirra(0,0,value);
}
void SC_Window::boxcolor_changed(int value){
    if(value != 0){
        sprite_prototype->vari = colorlist_values[value];
        sprite_prototype->UpdateColors();
        PisteDraw2_UpdateImage();
    }
    else PisteDraw2_RecoverImage();

    sprite_prototype->Piirra(0,0,currentframe);
}

//Internal Functions
void SC_Window::update(){
    ui->lab_sound->setText(sprite_prototype->aanitiedostot[0]);
}
