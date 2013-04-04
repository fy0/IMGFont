
#include "Font.h"
#include "Image.h"

#define FT_IS_SCALABLE( face ) \
          ( face->face_flags & FT_FACE_FLAG_SCALABLE )

map<string, FT2Font*> _fontCache;

FT2Font::FT2Font()
{
	ftLib = new FT_Library();
	ftFace = new FT_Face();
	FT_Init_FreeType(ftLib);
}

FT2Font* GetFont(const string& fontname)
{
	map<string, FT2Font*>::iterator it = _fontCache.find(fontname);
	if(it != _fontCache.end()) return it->second;
	return NULL;
}

FT2Font* LoadFont(const string& filename, const string& fontname, int pointsize, int faceindex)
{
	map<string, FT2Font*>::iterator it = _fontCache.find(fontname);
	if(it != _fontCache.end())
	{
		return NULL;
	}

	FT2Font* font = new FT2Font();

	if (FT_New_Face(*font->ftLib, filename.c_str(), faceindex, font->ftFace)) return NULL;
    //FT_Select_Charmap(*font->ftFace, FT_ENCODING_GB2312);
	FT_Select_Charmap(*font->ftFace, FT_ENCODING_UNICODE);

	//FT_Set_Pixel_Sizes(*font->ftFace, pointsize, pointsize);
	FT_Set_Char_Size(*font->ftFace, pointsize * 64.0f, pointsize * 64.0f, 96, 96);
 
	_fontCache[fontname] = font;
	return font;
}

float FT2Font::CharWidth()
{
	FT_Size ftSize = (*ftFace)->size;

    if( 0 == ftSize)
    {
        return 0.0f;
    }
    
    if( FT_IS_SCALABLE((*ftFace)))
    {
        return ( (*ftFace)->bbox.xMax - (*ftFace)->bbox.xMin) * ( static_cast<float>(ftSize->metrics.x_ppem) / static_cast<float>((*ftFace)->units_per_EM));
    }
    else
    {
        return static_cast<float>( ftSize->metrics.max_advance) / 64.0f;
    }
}

float FT2Font::CharHeight()
{
	FT_Size ftSize = (*ftFace)->size;

    if( 0 == ftSize)
    {
        return 0.0f;
    }
    
    if( FT_IS_SCALABLE((*ftFace)))
    {
        return ( (*ftFace)->bbox.yMax - (*ftFace)->bbox.yMin) * ( (float)ftSize->metrics.y_ppem / (float)(*ftFace)->units_per_EM);
    }
    else
    {
        return static_cast<float>( ftSize->metrics.height) / 64.0f;
    }
}

uint FT2Font::GetCharIndex(uint characterCode)
{
	return FT_Get_Char_Index(*ftFace, characterCode);
}

FT_GlyphSlot FT2Font::Glyph(uint index)
{
    FT_Load_Glyph(*ftFace, index, FT_LOAD_DEFAULT);
    FT_GlyphSlot ftGlyph = (*ftFace)->glyph;
	FT_Render_Glyph(ftGlyph, FT_RENDER_MODE_NORMAL);
	return ftGlyph;
}

CharBitmap* GetBitmap(FT_GlyphSlot glyph)
{
	Color fontcolor = GetFontColor();
	Color bgcolor = GetBackgroundColor();
	FT_Bitmap bitmap = glyph->bitmap;

	int width = bitmap.width;
	int height = bitmap.rows;

	byte* pBuf = new byte[width * height * 4];
	for(int i=0;i<width * height * 4;i+=4) {
		pBuf[i]   = bgcolor.R;
		pBuf[i+1] = bgcolor.G;
		pBuf[i+2] = bgcolor.B;
		pBuf[i+3] = bgcolor.A;
	}

    for(int j=0; j  < height ; j++)
    {
        for(int i=0; i < width; i++)
        {
            unsigned char _vl =  (i>=bitmap.width || j>=bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];

			if (_vl) {
				pBuf[(4*i + (height - j - 1) * width * 4)  ] = fontcolor.R;
				pBuf[(4*i + (height - j - 1) * width * 4)+1] = fontcolor.G;
				pBuf[(4*i + (height - j - 1) * width * 4)+2] = fontcolor.B;
				pBuf[(4*i + (height - j - 1) * width * 4)+3] = _vl * (fontcolor.A/255);
			}
        }
    }
	return new CharBitmap(width, height, pBuf);
}

void FreeBitmap(CharBitmap* ch)
{
	free(ch->buf);
	free(ch);
}
