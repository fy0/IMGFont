/**
 Õº∆¨º”‘ÿ°£2013.2.19
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "_base.h"

class Color {
public:
	Color() : R(0),G(0),B(0),A(0xFF) {};
	Color(byte R, byte G, byte B, byte A) : R(R),G(G),B(B),A(A) {};
	byte R,G,B,A;
};

void ImageInit();
const int LoadTexture(const string& fn);

void SetBackgroundColor(int R, int G, int B, int A=0xFF);
void SetFontColor(int R, int G, int B, int A=0xFF);

Color GetBackgroundColor();
Color GetFontColor();

ILuint ImgNew(int width, int height, byte* data=NULL, int channel=4, int Format=IL_RGBA);
void ImgSave(ILuint imgID, ILenum fileformat, const string& filename);

#endif
