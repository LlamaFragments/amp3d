//
//  renderer.h
//  
//
//  Created by Walker Henderson on 1/28/13.
//
//

#ifndef ____renderer__
#define ____renderer__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <GLUT/glut.h>
#include <png.h>

//Local includes
#include "lodepng.h"

using namespace std;

class Renderer
{
public:
    Renderer();
    bool Init();
    bool OpenWindow();
    void CloseWindow();
    void DrawFrame();
private:
    GLuint MakeBuffer(GLenum targetBuffer, const void* bufferData, GLsizei bufferSize);
    GLuint MakeTexture(const char * filename);
    
    GLuint MakeShader(GLenum type, const char * filename);
    GLuint MakeShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};
static struct
{
    GLuint vertexBuffer;
    GLuint elementBuffer;
    GLuint textures;
    
    GLuint vertexShader, fragmentShader, shaderProgram;
    struct {
        GLint textures;
    } uniforms;
    
    struct {
        GLint position;
    } attributes;
    
} g_resources;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f,
    1.0f, -1.0f,
    -1.0f,  1.0f,
    1.0f,  1.0f
};
static const GLushort g_element_buffer_data[] = { 0, 1, 2, 3 };

#endif /* defined(____renderer__) */