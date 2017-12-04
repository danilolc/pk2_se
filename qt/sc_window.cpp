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
#include "../src/constants.h"

AnimThread anim_thread;

void AnimThread::run(){
    active = true;
    while(active){
        if(this->window->animating)
            this->window->animate();
        QThread::usleep(16666);
    }
}

//Thread function
void SC_Window::animate(){
    int lastframe = currentframe;
    currentframe = sprite->Animoi();
    if(lastframe != currentframe){
        sprite_prototype->Piirra(0,0,currentframe);
        ui->box_frame->setValue(currentframe);
        framebox_list[sprite->sekvenssi_index]; //Change color or something
    }
}

void SC_Window::GetFrameSpinBoxes(){
    framebox_list[0] = ui->box_frame1;
    framebox_list[1] = ui->box_frame2;
    framebox_list[2] = ui->box_frame3;
    framebox_list[3] = ui->box_frame4;
    framebox_list[4] = ui->box_frame5;
    framebox_list[5] = ui->box_frame6;
    framebox_list[6] = ui->box_frame7;
    framebox_list[7] = ui->box_frame8;
    framebox_list[8] = ui->box_frame9;
    framebox_list[9] = ui->box_frameA;
}

SC_Window::SC_Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::SC_Window){
    ui->setupUi(this);
    this->GetFrameSpinBoxes();
    this->LinkSignals();

    sprite_prototype = new PK2Sprite_Prototyyppi;
    sprite_prototype->Uusi();

    sprite = new PK2Sprite(sprite_prototype,0,true,0,0);

    PisteDraw2_Start(ui->frame);

    //ui->lab_sound->setText("");
    //ui->lab_name->setText("");
    //ui->frame->setText("");

    anim_thread.window = this;

    //Create color list texts
    for(int i = 0; i < 8; i++)
        ui->box_color->addItem(colorlist[i]);

    this->updateAll();
}

SC_Window::~SC_Window(){
    anim_thread.active = false;
    while(anim_thread.isRunning());

    delete ui;
    delete sprite;
    delete sprite_prototype;
}

void SC_Window::LinkSignals(){
    //Menu
    connect(ui->menuOpen,    SIGNAL(triggered(bool)),         this, SLOT(open()));
    connect(ui->menuSave,    SIGNAL(triggered(bool)),         this, SLOT(save()));

    //Tab1
    connect(ui->box_color,   SIGNAL(currentIndexChanged(int)),this, SLOT(boxcolor_changed(int)));

    //Image

    //Animation
    connect(ui->box_animate, SIGNAL(stateChanged(int)),       this, SLOT(boxanimate_changed(int)));
    connect(ui->box_restart, SIGNAL(clicked()),               this, SLOT(restartanimation()));
    connect(ui->box_frame,   SIGNAL(valueChanged(int)),       this, SLOT(boxcurrentframe_changed(int)));
    connect(ui->box_curranim,SIGNAL(valueChanged(int)),       this, SLOT(boxcurrentanimation_changed(int)));
    connect(ui->box_interval,SIGNAL(valueChanged(int)),       this, SLOT(boxframeinterval_changed(int)));

    connect(framebox_list[0],SIGNAL(valueChanged(int)),       this, SLOT(boxframe0_changed(int)));
    connect(framebox_list[1],SIGNAL(valueChanged(int)),       this, SLOT(boxframe1_changed(int)));
    connect(framebox_list[2],SIGNAL(valueChanged(int)),       this, SLOT(boxframe2_changed(int)));
    connect(framebox_list[3],SIGNAL(valueChanged(int)),       this, SLOT(boxframe3_changed(int)));
    connect(framebox_list[4],SIGNAL(valueChanged(int)),       this, SLOT(boxframe4_changed(int)));
    connect(framebox_list[5],SIGNAL(valueChanged(int)),       this, SLOT(boxframe5_changed(int)));
    connect(framebox_list[6],SIGNAL(valueChanged(int)),       this, SLOT(boxframe6_changed(int)));
    connect(framebox_list[7],SIGNAL(valueChanged(int)),       this, SLOT(boxframe7_changed(int)));
    connect(framebox_list[8],SIGNAL(valueChanged(int)),       this, SLOT(boxframe8_changed(int)));
    connect(framebox_list[9],SIGNAL(valueChanged(int)),       this, SLOT(boxframe9_changed(int)));

}

void SC_Window::boxframe_changed(int value, int box_index){
    int currentanimation = sprite->animaatio_index;
    sprite_prototype->animaatiot[currentanimation].sekvenssi[box_index] = value + 1;
}

//Slots
void SC_Window::open(){
    QString file = QFileDialog::getOpenFileName(this,"Selecione um sprite.", "", "Sprites (*.spr)");

    if(!file.isEmpty()){

        if(anim_thread.isRunning()){
            anim_thread.active = false;
            while(anim_thread.isRunning());
        }

        this->filename = file;
        QByteArray bap = filename.toLatin1(); //Path
        QByteArray baf = bap; //File

        bap.data()[bap.lastIndexOf(DIR_SEP)+1] = '\0';
        baf.remove(0,bap.lastIndexOf('\0'));
        chdir(bap.data());

        sprite_prototype->Lataa(bap.data(),baf.data());

        anim_thread.start();

        this->updateAll();
    }
}
void SC_Window::save(){

}
void SC_Window::reset(){

}
void SC_Window::boxcurrentframe_changed(int value){
    currentframe = value;
    sprite_prototype->Piirra(0,0,value);
}
void SC_Window::boxcurrentanimation_changed(int value){
    sprite->animaatio_index = value;
    ui->txt_animationName->setText(animationlist[value]);
    this->updateFrameSpinBoxes();
}
void SC_Window::boxframeinterval_changed(int value){
    sprite_prototype->frame_rate = value;
}

void SC_Window::boxframe0_changed(int value){
    this->boxframe_changed(value,0);
}
void SC_Window::boxframe1_changed(int value){
    this->boxframe_changed(value,1);
}
void SC_Window::boxframe2_changed(int value){
    this->boxframe_changed(value,2);
}
void SC_Window::boxframe3_changed(int value){
    this->boxframe_changed(value,3);
}
void SC_Window::boxframe4_changed(int value){
    this->boxframe_changed(value,4);
}
void SC_Window::boxframe5_changed(int value){
    this->boxframe_changed(value,5);
}
void SC_Window::boxframe6_changed(int value){
    this->boxframe_changed(value,6);
}
void SC_Window::boxframe7_changed(int value){
    this->boxframe_changed(value,7);
}
void SC_Window::boxframe8_changed(int value){
    this->boxframe_changed(value,8);
}
void SC_Window::boxframe9_changed(int value){
    this->boxframe_changed(value,9);
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
void SC_Window::restartanimation(){
    sprite->sekvenssi_index = 0;
}

void SC_Window::updateFrameSpinBoxes(){
    int i;
    int currentanimation = sprite->animaatio_index;
    int nofframes = sprite_prototype->animaatiot[currentanimation].frameja;

    for(i = 0; i < nofframes; i++){
        framebox_list[i]->setValue(sprite_prototype->animaatiot[currentanimation].sekvenssi[i] - 1);
        framebox_list[i]->setEnabled(true);
        framebox_list[i]->setMaximum(sprite_prototype->frameja - 1);
        framebox_list[i]->setMinimum(0);
    }
    for(; i < 10 ; i++){
        framebox_list[i]->setValue(0);
        framebox_list[i]->setEnabled(false);
    }
}

//Internal Functions
void SC_Window::updateAll(){
    ui->lab_sound->setText(sprite_prototype->aanitiedostot[0]);
    ui->lab_name->setText(sprite_prototype->nimi);

    int color = sprite_prototype->vari;
    ui->box_color->setEnabled(true);
    for(int i = 0; i < 8; i++)
        if(colorlist_values[i] == color)
            ui->box_color->setCurrentIndex(i);

    ui->box_frame->setMaximum(sprite_prototype->frameja - 1);
    ui->box_frame->setMinimum(0);
    if(!animating){
        ui->txt_frame->setEnabled(true);
        ui->box_frame->setEnabled(true);
        ui->box_frame->setValue(0);
        this->boxcurrentframe_changed(0);
    }

    ui->box_animate->setEnabled(true);

    ui->txt_interval->setEnabled(true);
    ui->box_interval->setEnabled(true);
    ui->box_interval->setValue(sprite_prototype->frame_rate);
    ui->box_interval->setMinimum(0);
    ui->box_interval->setMaximum(255);

    ui->txt_animationName->setEnabled(true);
    ui->txt_animationName->setText(animationlist[sprite->animaatio_index]);
    ui->txt_curranim->setEnabled(true);
    //ui->txt_nofframes->setEnabled(true);
    ui->txt_frames->setEnabled(true);

    ui->box_restart->setEnabled(true);

    ui->box_curranim->setEnabled(true);
    ui->box_curranim->setValue(sprite->animaatio_index);
    ui->box_curranim->setMaximum(sprite_prototype->animaatioita);
    ui->box_curranim->setMinimum(0);
    this->updateFrameSpinBoxes();
}
