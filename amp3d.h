//
//  amp3d.h
//  
//
//  Created by Walker Henderson on 1/28/13.
//
//

#ifndef ____amp3d__
#define ____amp3d__

#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <GLUT/glut.h>
#include <stdexcept>
#include <dirent.h>
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

//Local includes
#include "renderer.h"
#include "slb/include/SLB/SLB.hpp"

class Component
{
public:
private:
};

class Behavior : public Component
{
public:
	void Update()
	{
		cout << "hey arnold!" << endl;
	}
private:
};

class Transform : public Component
{
public: 
	Transform()
	{
		std::cout << "Transform constructor "<< (void*) this << std::endl;
		position = glm::vec3(0,0,0);
	}

	~Transform()
	{
		std::cout << "Transform destructor " << (void*) this << std::endl;
	}

	Transform(const Transform &m)
	{
		std::cout << "Transform copy constructor from " << (void*) &m << " -> " << (void*) this << std::endl;
		position.x = m.position.x;
		position.y = m.position.y;
		position.z = m.position.z;

	}

	glm::vec3 getPosition()
	{
		return position;
	}

	void setPosition(float x, float y, float z)
	{
		position = glm::vec3(x, y, z);
	}
private:
	//std::string _string;
	//int _int;
	glm::vec3 position;
};

class FirstClass
{
public: 
	FirstClass() : _string(), _int(0)
	{
		std::cout << "FirstClass constructor "<< (void*) this << std::endl;
	}

	~FirstClass()
	{
		std::cout << "FirstClass destructor " << (void*) this << std::endl;
	}

	FirstClass(const FirstClass &m) : _string(m._string), _int(m._int)
	{
		std::cout << "FirstClass copy constructor from " << (void*) &m << " -> " << (void*) this << std::endl;
	}

	int getInt() const { return _int; }
	const std::string& getString() const { return _string; }
	void setInt(int i) { _int = i; }
	void setString(const std::string &s) { _string = s; }

private:
	std::string _string;
	int _int;

};

#endif /* defined(____amp3d__) */