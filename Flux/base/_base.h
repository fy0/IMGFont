
#ifndef _BASE_H
#define _BASE_H

#define FTGL_LIBRARY_STATIC
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4244) 

#if defined(WIN32)
	#include <windows.h>
#endif

#include <ft2build.h> 
#include FT_FREETYPE_H

#undef  _UNICODE
#include "IL/il.h"
#include "IL/ilut.h"
#define _UNICODE 1

#include <iconv.h> 

#include "string.h"

#include <set>
#include <map>
#include <list>
#include <deque>
#include <vector>
#include <string>
#include <iostream>

using std::set;
using std::map;
using std::list;
using std::deque;
using std::vector;
using std::string;
using std::wstring;

#define byte unsigned char
#define uint unsigned int

#define IL_PVR			0x0480
#define IL_PVR_RGBA2	0x047F
#define IL_PVR_RGBA4	0x0480
#define IL_PVR_RGBA8	0x0481

#endif
