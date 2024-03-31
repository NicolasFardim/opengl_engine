#include "geng.hpp"

bool	Geng::initWindow(const char* TITLE, int xpos, int	ypos, int width, int height)
{
	int				success;
	unsigned	int	window_flags;

	success	= true;
	window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cerr << "SDL failed to init. ERROR: " << SDL_GetError() << std::endl;
		return (success = false);
	}
	else
	{
		// OpenGl 3.2 context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		std::cout << "SDL Subsystem initialised... " << std::endl;
		Window = SDL_CreateWindow(TITLE, xpos, ypos, width, height, window_flags);
		if (Window == NULL)
		{
			std::cerr << "Unable to create Window. ERROR: " << SDL_GetError() << std::endl;
			return (success = false);
		}
		Context = SDL_GL_CreateContext(Window);
		if (Context == NULL)
		{
			std::cerr << "Unable to create Context. ERROR: " << SDL_GetError() << std::endl;
			return (success = false);
		}

		glClearColor(1.f, 0.f, 1.f, 0.f); // pink background

	}
	return (success);
}

// GLEW set up
bool	Geng::initGLEW()
{
	SDL_GL_MakeCurrent(Window, Context);
	bool	success = true;
	glewExperimental = GL_TRUE;
	GLenum	err = glewInit();
	GLuint 	vertexBuffer;

	if (GLEW_OK != err)
	{
		std::cerr << "Glew Failed to init. ERROR: " << glewGetErrorString(err) << std::endl;
		return (success = false);
	}
	else
		while (glGetError() != GL_NO_ERROR){}

	// check if glew is allright
	glGenBuffers(1, &vertexBuffer);
	std::cout << "GLEW test: " << vertexBuffer << std::endl;
	return (success);
}

void	Geng::handleEvent()
{
	SDL_Event	e;
	SDL_PollEvent(&e);
	if	(e.type == SDL_QUIT)
		runSet(false);
	switch (e.key.keysym.sym)
	{
		case SDLK_ESCAPE:
			runSet(false);
			break;
		default:
			break;
	}
}

void	Geng::update()
{
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(Window);
}

void	Geng::close()
{
	SDL_DestroyWindow(Window);
	SDL_GL_DeleteContext(Context);
	Window = NULL;
	Context = NULL;
	SDL_Quit();
	std::cout << "Terminated... " << std::endl;
}