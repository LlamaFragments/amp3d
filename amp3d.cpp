/*
 *
 *  amp3d.cpp
 *
 * Created by Walker Henderson on 1/28/13.
 *
 */

#include "amp3d.h"
//#import <Foundation/Foundation.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <GLUT/glut.h>
#include <stdexcept>
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

//Local includes
#include "renderer.h"

using namespace std;

//Lua interpreter
lua_State* L;

int main ( int argc, char *argv[] )
{
    Renderer renderer;
    //Init GLFW
    if (renderer.Init())
    {
        cout << "GLFW Init succeeded." << endl;
    }
    else
    {
        cout << "GLFW Init failed." << endl;
        throw runtime_error("GLFW Init failed.");
    }
    bool result = renderer.OpenWindow();
    if (result)
    {
        cout << "Window opened successfully!" << endl;
    }
    else
    {
        cout << "Window opening failed." << endl;
    }
    int running = GL_TRUE;
    
    // Main loop
    while( running )
    {
        renderer.DrawFrame();
        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
    }
    
    renderer.CloseWindow();
    
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
