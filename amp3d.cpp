/*
 *
 *  amp3d.cpp
 *
 * Created by Walker Henderson on 1/28/13.
 *
 */

#include "amp3d.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}


/* the Lua interpreter */

lua_State* L;

int main ( int argc, char *argv[] )
{
	/* initialize Lua */
	L = luaL_newstate();
    
	/* load various Lua libraries */

	luaL_openlibs(L);
    luaopen_table(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);
    
	/* cleanup Lua */

	lua_close(L);
    
	return 0;
}
