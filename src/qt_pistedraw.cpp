//#########################
//Pekka Kana QT Sprite Creator - qt_pistedraw.cpp
//by Danilo Lemos 2017
//#########################

//A simplified version of PisteDraw.cpp from PekkaKana 2
//Will hold the sprite frame

#include <QRect>
#include <QImage>
#include <QColor>
#include <QPainter>

#include <cstdio>

#include "pistedraw.h"
#include "types.h"

#define MAX_FRAMES 50

QLabel* screenframe = NULL;

bool loaded = false;
bool image_loaded = false;

QImage* image8 = NULL;
QImage* image8_bkp = NULL;
QImage* image = NULL;

QRect* frames[MAX_FRAMES];

int findfreeframe(){
    int i;
    for(i=1;i<MAX_FRAMES;i++)
        if(frames[i]==NULL)
            return i;
    return -1;
}

void PisteDraw2_UpdateImage(){
    if(!image_loaded) return;

    int w = image8->width();
    int h = image8->height();
    BYTE index;
    QRgb color;
    for(int x = 0; x < w; x++)
        for(int y = 0; y < h; y++){
            index = image8->pixelIndex(x,y);
            color = index == 255 ? Qt::transparent : image8->color(index);
            image->setPixel(x,y,color);
        }
}

int PisteDraw2_GetPalette(const char* filename){
    QImage buffer(filename);
    for(int i = 0; i < 256; i++)
        image8->setColor(i,buffer.color(i));
    PisteDraw2_UpdateImage();
    return 0;
}

int PisteDraw2_Image_Load(const char* filename, bool getPalette){
    for(int i=0;i<MAX_FRAMES;i++)
        frames[i] = NULL;

    if(image8 != NULL) delete image8;
    image8 = new QImage(filename);

    image8_bkp = new QImage(*image8);

    if(image != NULL) delete image;
    image = new QImage(image8->width(), image8->height(),QImage::Format_RGBA8888);

    image_loaded = true;
    PisteDraw2_UpdateImage();
    //screenframe->setPixmap(QPixmap::fromImage(*image));

    return 0;
}

void PisteDraw2_RecoverImage(){
    if(!image_loaded) return;

    delete image8;
    image8 = new QImage(*image8_bkp);
    PisteDraw2_UpdateImage();
}

int PisteDraw2_Image_Delete(int& index){
    if(index <= 0 || index >= MAX_FRAMES){
        index = -1;
        return -1;
    }
    if(frames[index]!=NULL){
        delete frames[index];
        index = -1;
        return 0;
    }
    else{
        index = -1;
        return -1;
    }
}

int PisteDraw2_Image_Cut(int ImgIndex, int x, int y, int w, int h){
    int index = findfreeframe();
    if(index == -1) return -1;
    frames[index] = new QRect(x,y,w,h);
    return index;
}

int PisteDraw2_Image_FlipHori(int index){
    //int w = frames[index]->width();
    //frames[index]->setWidth(-w);
    return 0;
}

int PisteDraw2_Image_Clip(int index, int x, int y){
    if(!image_loaded) return -1;

    QImage spr = image->copy(*frames[index]);
    screenframe->setPixmap(QPixmap::fromImage(spr));
    return 0;
}

void PisteDraw2_Image_GetSize(int index, int& w, int& h){
    if(index == 0){
        w = image8->width();
        h = image8->height();
        return;
    }
    w = frames[index]->width();
    h = frames[index]->width();
    if(w < 0) w *= -1;
}

int PisteDraw2_DrawImage_Start(int index, BYTE *&pixels, DWORD &pitch){
    pixels = (BYTE*) image8->bits();
    pitch = image8->bytesPerLine();
}

int PisteDraw2_DrawImage_End(int index){
    PisteDraw2_UpdateImage();
}

int PisteDraw2_Start(QLabel* frame){
    if (loaded) return -1;

    screenframe = frame;

    for(int i=0;i<MAX_FRAMES;i++)
        frames[i] = NULL;

    loaded = true;
    return 0;
}

int PisteDraw2_Exit(){
    //TODO - delete all
    loaded = false;
}
