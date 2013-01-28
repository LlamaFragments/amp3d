//
//  renderer.cpp
//  
//
//  Created by Walker Henderson on 1/28/13.
//
//

#include "renderer.h"
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <GLUT/glut.h>

glm::vec2 SCREEN_SIZE(1680, 1050);

Renderer::Renderer()
{
    
}

bool Renderer::Init()
{
    //Return true if everything init'd properly
    bool s = true;
    s = s && glfwInit();
    return s;
}

bool Renderer::OpenWindow()
{
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    int s1 = glfwOpenWindow(
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
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    int s2 = glewInit();
    return (bool) s1 && (bool) s2;
}

void Renderer::CloseWindow()
{
    //glfwCloseWindow();
    glfwTerminate();
}

void Renderer::DrawFrame()
{
    // OpenGL rendering goes here...
    glClear( GL_COLOR_BUFFER_BIT );
    // Swap front and back rendering buffers
    glfwSwapBuffers();
}