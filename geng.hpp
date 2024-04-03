#ifndef	GENG_HPP
#define	GENG_HPP

// defines
#define GL_GLEXT_PROTOTYPES
#define	GLEW_STATIC

// libs
#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

#include <fstream>
#include <sstream>
#include <string>

#include <vector>

class Geng
{
private:
	SDL_Window*		Window;
	SDL_GLContext	Context;
	GLuint			vertexBuffer;
	bool			isRuning;
public:
	bool	initWindow(const char* TITLE, int	xpos, int	ypos, int	width,	int	height);
	bool	initGLEW();
	void	handleEvent();
	void	update();
	void	draw();
	void	runSet(bool set) {isRuning = set;};
	bool	runing() {return isRuning;};
	void	close();
};

class ShaderInit
{
private:
	std::string readShaderSource(const std::string& filepath);
public:
	GLuint	make_module(const std::string& filepath, unsigned int module_type);
	GLuint	make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
};

class TriangleMesh
{
private:
	unsigned int VBO, VAO, vertex_count;
public:
	TriangleMesh();
	void draw();
	~TriangleMesh();
};

#endif
