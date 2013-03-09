/*
 *
 *  amp3d.cpp
 *
 * Created by Walker Henderson on 1/28/13.
 *
 */

#include "amp3d.h"
//#import <Foundation/Foundation.h>

using namespace std;

void doWrappers(SLB::Manager *m)
{
    std::cout << "Loading wrappers..." << std::endl;
    // this will register the wrapper of FirstClass
    SLB::Class< Transform >("Transform",m)
        // a comment/documentation for the class [optional]
        .comment("This is our wrapper of Transform class!!")
        // empty constructor, we can also wrapper constructors
        // with arguments using .constructor<TypeArg1,TypeArg2,..>()
        .constructor()
        // a method/function/value...
        .set("getPosition", &Transform::getPosition)
            // comment of the method [optional]
            .comment("Returns the internal position")
        .set("setPosition", &Transform::setPosition)
            .comment("sets the internal position")
            // comment of the first parameter [optional]
            .param("x value")
            .param("y value")
            .param("z value")
    ;
    auto_ptr<Behavior> t;
    SLB::Class< Behavior >("Behavior", m)
        .constructor()
        .set("Update", &Behavior::Update)
        .inherits< Component >()
    ;
};

struct MyScript : public SLB::Script
{
public:
    MyScript(const char *code)
    {
        const char *lua_code = code
        ;
        
        // load the code inside the script
        doString(lua_code);
    }

    void invokeFooMethod()
    {
        lua_State *L = getState();
        // prepare a call object
        SLB::LuaCall<void()> call(L,"test");
        // perform the call with the parameters
        call();
    }
};

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
    
    /*cout << "starting this stuff" << endl;
    SLB::Manager m;
    doWrappers(&m);
    SLB::Script s(&m);
    DIR *pDIR;
    std::stringstream buffer;
    struct dirent *entry;
    if( pDIR=opendir("./scripts") ){
            while(entry = readdir(pDIR)){
                    if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
                    {
                        ifstream f;
                        string s1(entry->d_name);
                        string s2("scripts/");
                        s2 += s1;
                        f.open(s2.c_str(), std::ios::in | std::ios::binary);
                        cout << entry->d_name << endl;
                        if(!f.is_open()){
                            cerr << "File not found/something went wrong" << endl;
                        }
                        //Put file into buffer
                        
                        buffer << f.rdbuf();
                        buffer << '\n';
                        f.close();
                    }
                    //cout << entry->d_name << "\n";

            }
            closedir(pDIR);
    }
    string lua_code = buffer.str();
    glm::vec3 v1(0, 3.5f, 2.5f);
    glm::vec3 v2(1.0f, 1.0f, 1.0f);
    glm::vec3 v3 = v1 + v2;
    //cout << v3.x << endl;
    MyScript ms(lua_code.c_str());
    ms.invokeFooMethod();*/
    /*
    s.safeDoString(lua_code.c_str());
    
    //lua_State *L = s.getState();
        // prepare a call object
    //SLB::LuaCall call(L,"test");
        // perform the call with the parameters
    //call();
    SLB::LuaCall<int()>call(s.getState(),"test");
    call(2);
    //luaL_dostring(L, lua_code.c_str()); // execute code
    cout << s.getLastError() << endl;
    */

    /*
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
    */
	return 0;
}
