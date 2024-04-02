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

class ShaderScr
{
private:
	std::ifstream		file;
	std::stringstream	bufferedLines;
	std::string			line;

public:
	bool	checkfile(const std::string& filepath);
	unsigned	int make_module(const std::string& filepath, unsigned int module_type);
};

#endif
