//#########################
//Pekka Kana QT Sprite Creator - qt_pistedraw.cpp
//by Danilo Lemos 2017
//#########################

//A simplified version of PisteDraw.cpp from PekkaKana 2
//Will hold the screen scene

#include "pistedraw.h"

QPixmap* pixmap;

int PisteDraw2_Image_Load(const char* filename, bool getPalette){

}

int PisteDraw2_Image_Delete(int& index){

}

int PisteDraw2_Image_Cut(int ImgIndex, int x, int y, int w, int h){

}

int PisteDraw2_Image_FlipHori(int index){

}

int PisteDraw2_Image_Clip(int index, int x, int y){

}

void PisteDraw2_Image_GetSize(int index, int& w, int& h){

}

int PisteDraw2_DrawImage_Start(int index, BYTE *&pixels, DWORD &pitch){

}

int PisteDraw2_DrawImage_End(int index){

}

QPixmap* PisteDraw2_Start(int width, int height){
    pixmap = new QPixmap(width,height);
    pixmap->fill(Qt::white);


    return pixmap;
}

int PisteDraw2_Exit(){

}

void PisteDraw2_Update(bool draw){

}
