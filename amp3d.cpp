/*
 *
 *  amp3d.cpp
 *
 * Created by Walker Henderson on 1/28/13.
 *
 */

#include "amp3d.h"
#include <GL/glfw.h>
#include <iostream>
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

using namespace std;

//Lua interpreter
lua_State* L;

int main ( int argc, char *argv[] )
{
    //Init GLFW
    glfwInit();
    //glfwOpenWindowHint(GLFW_OPENGL_PROFILE, 0);
    int result = glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
    if (result == GL_TRUE)
    {
        cout << "worked!" << endl;
    }
    else
    {
        cout << "failed" << endl;
    }
    int running = GL_TRUE;
    // Main loop
    while( running )
    {
        // OpenGL rendering goes here...
        glClear( GL_COLOR_BUFFER_BIT );
        // Swap front and back rendering buffers
        glfwSwapBuffers();
        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) &&
        glfwGetWindowParam( GLFW_OPENED );
    }
    
    //glfwCloseWindow();
    glfwTerminate();
    
	//Initialize Lua
	L = luaL_newstate();
    
	//Load various Lua libraries
	luaL_openlibs(L);
    luaopen_table(L);
    luaopen_io(L);
    luaopen_string(L);
    luaopen_math(L);
    //Run the lua script
	luaL_dofile(L, "lua_script.lua");
	
    //Clean up Lua
	lua_close(L);
    
	return 0;
}
