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
#include <iostream>
#include <stdexcept>
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

using namespace std;

//Lua interpreter
lua_State* L;

glm::vec2 SCREEN_SIZE(1680, 1050);

static struct
{
    GLuint vertexBuffer;
    GLuint elementBuffer;
    GLuint textures[2];
} threeddata;

int main ( int argc, char *argv[] )
{
    int * bagel = malloc(10 * sizeof(int));
    //Init GLFW
    if (glfwInit())
    {
        cout << "GLFW Init succeeded." << endl;
    }
    else
    {
        cout << "GLFW Init failed." << endl;
        throw runtime_error("GLFW Init failed.");
    }
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    int result = glfwOpenWindow(
                                //width
                                SCREEN_SIZE.x,
                                //height
                                SCREEN_SIZE.y,
                                //r/g/b bits
                                8,
                                8,
                                8,
                                //a bits
                                8,
                                //depth bits
                                8,
                                //stencil bits
                                8,
                                //mode
                                GLFW_FULLSCREEN);
    if (result)
    {
        cout << "Window opened successfully!" << endl;
    }
    else
    {
        cout << "Window opening failed." << endl;
    }
    
    glewInit();
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    int running = GL_TRUE;
    // Main loop
    while( running )
    {
        // OpenGL rendering goes here...
        glClear( GL_COLOR_BUFFER_BIT );
        // Swap front and back rendering buffers
        glfwSwapBuffers();
        // Check if ESC key was pressed or window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
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
