
class FT2Font {
	friend FT2Font* LoadFont(const string& filename, const string& fontname, int pointsize);
	friend FT2Font* GetFont(const string& fontname);
public:
	FT_Face* ftFace;
	FT_Library* ftLib;
	FT2Font();
	float CharWidth();
	float CharHeight();
	FT_GlyphSlot Glyph( unsigned int characterCode);
};

FT2Font* GetFont(const string& fontname);
FT2Font* LoadFont(const string& filename, const string& fontname, int pointsize, int faceindex=0);
