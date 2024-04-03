#include "geng.hpp"

/*
	TODO
	resizable window, fullscreen, etc... (sdl does not support drag window to resize)
	add color to some messages
*/

Geng			*Game = nullptr;
ShaderInit		*Shaders = nullptr;
TriangleMesh	*Triangle = nullptr;

int	main()
{
	Game = new Geng();
	Shaders = new  ShaderInit();
	GLuint	IntShader;

	if(!Game->initWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768))
	{
		std::cerr << "Unable to initialise Window." << std::endl;
		return -1;
	}
	if(!Game->initGLEW())
	{
		std::cerr << "Unable to initialise GLEW." << std::endl;
		return -2;
	}
	else
	{
		Triangle = new TriangleMesh();
		IntShader = Shaders->make_shader("../roo2/shaders/vertex_shader.txt", "../roo2/shaders/fragment_shader.txt");
		Game->runSet(true);
		while (Game->runing())
		{
			Game->handleEvent();
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(IntShader);
			Triangle->draw();
			Game->update();
		}
	}
	Game->close();
}
