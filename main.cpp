#include "geng.hpp"

/*
	TODO
	resizable window, fullscreen, etc... (sdl does not support drag window to resize)
*/

Geng	*BasicGame = nullptr;
ShaderScr	*SourceShader = nullptr;

int	main()
{
	BasicGame = new Geng();
	SourceShader = new  ShaderScr();

	SourceShader->checkfile("../roo2/shaders/vertex_shader.txt");
	SourceShader->checkfile("../roo2/shaders/fragment_shader.txt");
	SourceShader->checkfile("../roo2/shaders/compiling_shader.txt");
	if(!BasicGame->initWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768))
	{
		std::cerr << "Unable to initialise Window." << std::endl;
		return -1;
	}
	if(!BasicGame->initGLEW())
	{
		std::cerr << "Unable to initialise GLEW." << std::endl;
		return -2;
	}
	else
	{
		BasicGame->runSet(true);
		while (BasicGame->runing())
		{
			BasicGame->handleEvent();
			BasicGame->update();
		}
	}
	BasicGame->close();
}
