/**
 ���2013.3.31
*/

#ifndef UTILS_H
#define UTILS_H

#include "_base.h"
#include "Font.h"
#include "Image.h"

//enum FontMode {COMPACT, BLOCK};
//void SetFontMode(FontMode mode);
//FontMode GetFontMode();

typedef struct CharInfo {
	uint ch;
	uint index;
	int x;
	int y;
	int width;
	int height;

	int left;
	int right;
	int top;
	int bottom;
} CharInfo;

typedef struct GlyphInfo {
	ILuint img;
	int width;
	int height;
	int charnum;
	int linenum;
	vector<CharInfo*> chs;
} GlyphInfo;

GlyphInfo* MakeGlyph(FT2Font *f, const string& s, int maxwidth, int maxheight=0);

void SetLineGap(int linegap);
int GetLineGap();

void SetLineHeight(int lineheight);
int GetLineHeight();

#endif
