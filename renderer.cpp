//
//  renderer.cpp
//  
//
//  Created by Walker Henderson on 1/28/13.
//
//

#include "renderer.h"

glm::vec2 SCREEN_SIZE(1280, 800);

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

GLuint vao;

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
                                GLFW_WINDOW);
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glewExperimental = GL_TRUE;
    glewInit();

    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    //Set everything up
    g_resources.vertexBuffer = MakeBuffer(GL_ARRAY_BUFFER, g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
    g_resources.elementBuffer = MakeBuffer(GL_ELEMENT_ARRAY_BUFFER, g_element_buffer_data, sizeof(g_element_buffer_data));
    g_resources.textures = MakeTexture("image.png");
    g_resources.vertexShader = MakeShader(GL_VERTEX_SHADER, "shaders/vertex.vert");
    g_resources.fragmentShader = MakeShader(GL_FRAGMENT_SHADER, "shaders/fragment.frag");
    g_resources.shaderProgram = MakeShaderProgram(g_resources.vertexShader, g_resources.fragmentShader);
    g_resources.uniforms.textures = glGetAttribLocation(g_resources.shaderProgram, "textures");
    g_resources.attributes.position = glGetAttribLocation(g_resources.shaderProgram, "position");
    g_resources.attributes.color = glGetAttribLocation(g_resources.shaderProgram, "color");
    
    return (bool) s1;
}

void Renderer::CloseWindow()
{
    glfwTerminate();
}

void Renderer::DrawFrame()
{
    glClearColor( 0.0f, 0.0f, 0.5f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    //Use shader program
    glUseProgram(g_resources.shaderProgram);
    //Set up attribute pointers for vertex position and color, and textures.
    glVertexAttribPointer( g_resources.attributes.position,  2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0 );
    glVertexAttribPointer( g_resources.attributes.color,  3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid *)(2 * sizeof(float)) );
    GLint texAttrib = glGetAttribLocation( g_resources.shaderProgram, "texcoord" );
    glEnableVertexAttribArray( texAttrib );
    glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid*)( 5 * sizeof(float) ) );
    //Enable attribute arrays
    glEnableVertexAttribArray(g_resources.attributes.position);
    glEnableVertexAttribArray(g_resources.attributes.color);
    //Draw
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0 );
    //Disable attribute arrays
    glDisableVertexAttribArray(g_resources.attributes.position);
    glDisableVertexAttribArray(g_resources.attributes.color);
    //Swap buffers
    glfwSwapBuffers();
}

GLuint Renderer::MakeBuffer(GLenum targetBuffer, const void* bufferData, GLsizei bufferSize)
{
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(targetBuffer, buffer);
    glBufferData(targetBuffer, bufferSize, bufferData, GL_STATIC_DRAW);
    return buffer;
}

GLuint Renderer::MakeTexture(const char * filename)
{
    GLuint texture;
    
    unsigned w, h;
    std::vector<unsigned char> pixels;
    lodepng::decode(pixels, w, h, filename);
    glGenTextures(1, &texture);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,  pixels.data() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    return texture;
}

static void show_info_log(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
    GLint log_length;
    char *log;
    glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
    log = (char* )malloc(log_length);
    glGet__InfoLog(object, log_length, NULL, log);
    fprintf(stderr, "%s", log);
    free(log);
}

GLuint Renderer::MakeShader(GLenum type, const char * filename)
{   
    //open file
    std::ifstream f;
    f.open(filename, std::ios::in | std::ios::binary);
    if(!f.is_open()){
        cerr << "File not found/something went wrong" << endl;
    }
    //Put file into buffer
    std::stringstream buffer;
    buffer << f.rdbuf();
    string a = buffer.str();
    GLchar const * shaderText = a.c_str();

    GLuint shader;
    shader = glCreateShader(type);
    //Add the shader text to the shader and compile it
    glShaderSource(shader, 1, (const GLchar**)&shaderText, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    //Print stuff if something goes wrong
    if (!success)
    {
        fprintf(stderr, "Failed to compile shader %s:\n", filename);
        show_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint Renderer::MakeShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    //Create new shader program
    GLuint program = glCreateProgram();
    //Bind vertex and fragment shaders to the program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    //Set up output of fragment shader
    glBindFragDataLocation(program, 0, "finalColor" );
    //Link the shaders
    glLinkProgram(program);
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    //Output an error if something went wrong
    if (!success)
    {
        fprintf(stderr, "Failed to link shader program:\n");
        show_info_log(program, glGetProgramiv, glGetProgramInfoLog);
        glDeleteProgram(program);
        return 0;
    }
    return program;
}


