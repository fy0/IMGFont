%module flux
%{
#include "base/Font.h"
#include "base/Image.h"
#include "base/Utils.h"
%}

%include <std_string.i>
//%include <std_vector.i>
typedef std::string string;

#define byte unsigned char
#define uint unsigned int

%include "font.i"
%include "image.i"
%include "utils.i"
%include "devil.i"

#ifdef SWIGLUA
%typemap(out) std::vector<String>
%{
	{
		lua_newtable(L);
		
		if ($1.size() > 0)
		{
			for (unsigned int i=1; i <= $1.size(); i++)
			{
				lua_pushnumber(L, i);
				lua_pushstring(L, $1.at(i-1).c_str()); 
				lua_rawset(L, -3);
			}
		}
		
		SWIG_arg += 1; 
	}
%}
#endif
