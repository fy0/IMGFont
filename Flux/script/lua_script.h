/**
 lua ½Å±¾Ö§³Ö¡£2013.3.14
*/

#ifndef LUA_SCRIPT_H
#define LUA_SCRIPT_H

extern "C"
{	
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include "../base/_base.h"

class LuaScript {
public:
	static void Init();
	static void Finalize();
	static void Eval(const string& code);
	static void LoadFile(const string& fn);
	static lua_State* GetLuaState();
protected:
	static bool isInit;
	static lua_State *L;
};

#endif
