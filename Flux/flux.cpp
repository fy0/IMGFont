
#include "flux.h"

int main(int argc, char* argv[])
{
	ImageInit();
	LuaScript::Init();
	LuaScript::LoadFile("game.lua");
	getchar();
	LuaScript::Finalize();
	return 0;
}
