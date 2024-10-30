#include "geng.hpp"

/*
	TODO
	resizable window, fullscreen, etc... (sdl does not support drag window to resize)
	add color to some messages
*/

Geng			*Game = nullptr;
ShaderInit		*Shader = nullptr;
TriangleMesh	*Triangle = nullptr;

int	main()
{
	Game = new Geng();

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
		Shader = new ShaderInit("shaders/vertex_shader.txt", "shaders/fragment_shader.txt");
		Triangle = new TriangleMesh();
		Game->runSet(true);
		while (Game->runing())
		{
			Game->handleEvent();
			glClear(GL_COLOR_BUFFER_BIT);
			Shader->Use();
			Triangle->draw();
			Game->update();
		}
	}
	Game->close();
}
