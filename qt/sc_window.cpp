//#########################
//Pekka Kana QT Sprite Creator - sc_window.cpp
//by Danilo Lemos 2017
//#########################

#include <QFileDialog>
#include <QPixmap>
#include <QTimer>
#include <unistd.h>
#include <cstdio>
#include "sc_window.h"
#include "ui_sc_window.h"

#include "../src/pistedraw.h"
#include "../src/platform.h"
#include "../src/types.h"

AnimThread* anim_thread;

void AnimThread::run(){
    active = true;
    while(active){
        if(this->window->animating)
            this->window->animate();
        QThread::usleep(16666);
    }
}

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

    sprite = new PK2Sprite(sprite_prototype,0,true,0,0);

    PisteDraw2_Start(ui->frame);

    ui->lab_sound->setText("");
    ui->lab_name->setText("");

    ui->frame->setText("");

    anim_thread = new AnimThread();
    anim_thread->window = this;

    for(int i = 0; i < 8; i++)
        ui->box_color->addItem(colorlist[i]);
}

SC_Window::~SC_Window(){
    anim_thread->active = false;
    while(anim_thread->isRunning());
    delete anim_thread;

    delete ui;
    delete sprite;
    delete sprite_prototype;
}

//Slots
void SC_Window::open(){
    QString file = QFileDialog::getOpenFileName(this,"Selecione um sprite.", "", "Sprites (*.spr)");

    if(!file.isEmpty()){

        if(anim_thread->isRunning()){
            anim_thread->active = false;
            while(anim_thread->isRunning());
        }

        this->filename = file;
        QByteArray bap = filename.toLatin1(); //Path
        QByteArray baf = bap; //File

        bap.data()[bap.lastIndexOf(DIR_SEP)+1] = '\0';
        baf.remove(0,bap.lastIndexOf('\0'));
        chdir(bap.data());

        sprite_prototype->Lataa(bap.data(),baf.data());

        anim_thread->start();

        this->update();
    }
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

void SC_Window::boxanimate_changed(int value){
    bool check = value;
    ui->box_frame->setEnabled(!check);
    ui->txt_frame->setEnabled(!check);
    animating = check;
}

//Thread function
void SC_Window::animate(){
    int lastframe = currentframe;
    currentframe = sprite->Animoi();
    if(lastframe != currentframe){
        sprite_prototype->Piirra(0,0,currentframe);
        ui->box_frame->setValue(currentframe);
    }
}

//Internal Functions
void SC_Window::update(){
    ui->lab_sound->setText(sprite_prototype->aanitiedostot[0]);
    ui->lab_name->setText(sprite_prototype->nimi);

    ui->box_frame->setMaximum(sprite_prototype->frameja - 1);
    if(!animating){
        ui->txt_frame->setEnabled(true);
        ui->box_frame->setEnabled(true);
        ui->box_frame->setValue(0);
        this->boxframe_changed(0);
    }

    ui->box_animate->setEnabled(true);

    int color = sprite_prototype->vari;
    ui->box_color->setEnabled(true);
    for(int i = 0; i < 8; i++)
        if(colorlist_values[i] == color)
            ui->box_color->setCurrentIndex(i);
}
