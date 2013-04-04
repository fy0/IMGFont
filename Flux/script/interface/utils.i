
typedef std::vector vector;

typedef struct CharInfo {
	uint ch;
	uint index;
	int x;
	int y;
	int left;
	int width;
	int height;
	int xadvance;
} CharInfo;

%{

void lua_pushcharinfo(lua_State *L, void*ptr)
{
	SWIG_NewPointerObj(L, ptr, SWIGTYPE_p_CharInfo, 0);
}

%}

#ifdef SWIGLUA

%typemap(out) std::vector<CharInfo*>
%{
	{
		lua_newtable(L);
		
		if ($1.size() > 0)
		{
			for (unsigned int i=1; i <= $1.size(); i++)
			{
				lua_pushnumber(L, i);
				lua_pushcharinfo(L, $1.at(i-1)); 
				lua_rawset(L, -3);
			}
		}
		
		SWIG_arg += 1; 
	}
%}

#endif

typedef struct GlyphInfo {
	ILuint img;
	int linenum;
	//vector<CharInfo> chs;
} GlyphInfo;

%extend GlyphInfo {
	std::vector<CharInfo*> getchs() {return $self->chs;}
};

GlyphInfo* MakeGlyph(FT2Font *f, const string& s, int maxwidth);

void SetLineGap(int linegap);
int GetLineGap();
