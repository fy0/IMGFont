
#include "lua_script.h"

bool LuaScript::isInit = false;
lua_State* LuaScript::L = NULL;

extern "C"
{
	int luaopen_flux(lua_State* L);
}

void LuaScript::LoadFile(const string& fn)
{
	//lua_pushscreen(L, (void*)scr);
	//lua_setglobal(L, "theScreen");
	int error = luaL_dofile(L, fn.c_str());
	if (error) {
		const char* errs = lua_tostring(L, -1);
		printf("ERROR: %s\n", errs);
		lua_gc(L, LUA_GCCOLLECT, 0); // garbage collect on error
	}
}

void LuaScript::Init()
{
	L = luaL_newstate();
	lua_gc(L, LUA_GCSTOP, 0);
	luaL_openlibs(L);
	luaopen_flux(L);
	lua_gc(L, LUA_GCRESTART, 0);
	
	isInit = true;
}

void LuaScript::Finalize()
{
	lua_close(L);
}

void LuaScript::Eval(const string& code)
{
	if (!isInit)
	{
		return;
	}

	if (luaL_loadstring(L, code.c_str()))
	{
		string error(lua_tostring(L, -1));
		lua_pop(L, 1);
	
		std::cout<<"ERROR: "<<error<<std::endl;
		return;
	}
	else
	{
		if (lua_pcall(L, 0, LUA_MULTRET, 0 ))
		{
			const char* errs = lua_tostring(L, -1);
			//sysLog.Printf("ERROR: %s\n", errs);
			// error, will be in the stack trace
			lua_gc(L, LUA_GCCOLLECT, 0); // garbage collect on error
		}
	}
	// print out any return values left on the stack
	if (lua_gettop(L) > 0)
	{
		lua_getglobal(L, "print");
		lua_insert(L, 1);
		lua_pcall(L, lua_gettop(L)-1, 0, 0);
	}
	
	lua_settop(L, 0);
}

lua_State* LuaScript::GetLuaState()
{
	return L;
}
