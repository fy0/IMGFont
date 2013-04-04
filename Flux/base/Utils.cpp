
#include "Utils.h"

int _linegap = 0;

/*FontMode fontmode = COMPACT;

void SetFontMode(FontMode mode)
{
	fontmode = mode;
}

FontMode GetFontMode()
{
	return fontmode;
}*/

inline std::wstring __StringToWString(const std::string& s)
{
	std::locale chs("chs");
	std::locale::global(chs);
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	_Dest=0;
	std::locale::global(std::locale::classic());
	return result;
}

void SetLineGap(int linegap)
{
	_linegap = linegap;
}

int GetLineGap()
{
	return _linegap;
}

GlyphInfo* MakeGlyph(FT2Font *f, const string& s, int maxwidth)
{
	wstring str = __StringToWString(s);
	int len = str.length();
	int charHeight = f->CharHeight() + _linegap;
	GlyphInfo* ret = new GlyphInfo();
	ret->chs.resize(len);

	int xoffset = 0;
	int yoffset = 0;
	int linenum = 1;
	
	for (int i=0;i<len;i++) {
		FT_GlyphSlot ftGlyph = f->Glyph(f->GetCharIndex(str[i]));
		int offset = ftGlyph->bitmap_left + ftGlyph->bitmap.width;
		if ((xoffset + offset) > maxwidth) {
			linenum ++;
			xoffset = 0;
		}
		xoffset += offset;
	}

	xoffset = 0;
	yoffset = charHeight*(linenum-1);
	ILuint img = ImgNew(maxwidth, charHeight*linenum);

	for (int i=0;i<len;i++) {
		uint index = f->GetCharIndex(str[i]);
		FT_GlyphSlot ftGlyph = f->Glyph(index);
		CharBitmap* ch = GetBitmap(ftGlyph);
		ILuint chimg = ImgNew(ch->width, ch->height, ch->buf);

		ILubyte *data = ilGetData();
		int depth = ilGetInteger(IL_IMAGE_DEPTH);
		int Ascender = (*f->ftFace)->size->metrics.ascender >> 6;

		ilBindImage(img);
		int offset = ftGlyph->bitmap_left + ch->width;
		if ((xoffset + offset) > maxwidth) {
			yoffset -= charHeight;
			xoffset = 0;
		}

		xoffset += ftGlyph->bitmap_left;
		int y = charHeight-ch->height-(Ascender-ftGlyph->bitmap_top)+yoffset;

		ret->chs[i] = new CharInfo();
		ret->chs[i]->ch = (uint)(str[i]);
		ret->chs[i]->index = index;
		ret->chs[i]->left = ftGlyph->bitmap_left;
		ret->chs[i]->height = ch->height;
		ret->chs[i]->width = ch->width;
		ret->chs[i]->xadvance = ftGlyph->advance.x/64.0f - ftGlyph->bitmap_left - ch->width;
		ret->chs[i]->x = xoffset;
		ret->chs[i]->y = y;

		ilSetPixels(xoffset,y,0, ch->width,ch->height,depth, IL_RGBA, IL_UNSIGNED_BYTE, data);
		xoffset += ch->width;

		FreeBitmap(ch);
		ilDeleteImage(chimg);
	}

	ret->img = img;
	ret->linenum = linenum;
	return ret;
}
