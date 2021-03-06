//#########################
//PisteEngine - PisteDraw.h
//by Janne Kivilahti from Piste Gamez
//#########################

//A simplified version of PisteDraw.cpp from PekkaKana 2

#ifndef P_DRAW
#define P_DRAW

#include "types.h"
#include <QLabel>

struct PD_RECT{
	int x, y, w, h;
};

int PisteDraw2_GetPalette(const char* filename);
void PisteDraw2_UpdateImage();
void PisteDraw2_RecoverImage();

int PisteDraw2_Image_Load(const char* filename, bool getPalette);
int PisteDraw2_Image_Delete(int& index);
int PisteDraw2_Image_Cut(int ImgIndex, int x, int y, int w, int h);
int PisteDraw2_Image_FlipHori(int index);
int PisteDraw2_Image_Clip(int index, int x, int y);
void PisteDraw2_Image_GetSize(int index, int& w, int& h);
int PisteDraw2_DrawImage_Start(int index, BYTE *&pixels, DWORD &pitch);
int PisteDraw2_DrawImage_End(int index);

int PisteDraw2_Start(QLabel* frame);
int PisteDraw2_Exit();

#endif
