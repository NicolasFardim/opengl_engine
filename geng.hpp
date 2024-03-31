#ifndef	GENG_HPP
#define	GENG_HPP

// defines
#define GL_GLEXT_PROTOTYPES
#define	GLEW_STATIC

// libs
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <iostream>

class Geng
{
private:
	SDL_Window*		Window;
	SDL_GLContext	Context;
	bool			isRuning;
public:
	bool	initWindow(const char* TITLE, int	xpos, int	ypos, int	width,	int	height);
	bool	initGLEW();
	void	handleEvent();
	void	update();
	void	runSet(bool set) {isRuning = set;};
	bool	runing() {return isRuning;};
	void	close();
};

#endif
