/**
 �ֿ⡣2013.3.30
*/

#ifndef FONT_H
#define FONT_H

#include "_base.h"

class FT2Font {
	friend FT2Font* LoadFont(const string& filename, const string& fontname, int pointsize, int faceindex);
	friend FT2Font* GetFont(const string& fontname);
public:
	FT_Face* ftFace;
	FT_Library* ftLib;
	FT2Font();
	float CharWidth();
	float CharHeight();
	uint GetCharIndex(uint characterCode);
	FT_GlyphSlot Glyph(uint index);
};

class CharBitmap {
public:
	CharBitmap(int width, int height,byte* buf){this->width=width;this->height=height;this->buf=buf;};
	int width;
	int height;
	byte* buf;
};

FT2Font* LoadFont(const string& filename, const string& fontname, int pointsize, int faceindex=0);
FT2Font* GetFont(const string& fontname);
CharBitmap* GetBitmap(FT_GlyphSlot glyph);
void FreeBitmap(CharBitmap* ch);

#endif
