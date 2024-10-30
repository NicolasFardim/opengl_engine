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
	std::string readShaderSource(const std::string& filePath);
public:
	int	Attributes;
	GLuint shaderProgram;

	// constructor reads, build and link shaders.
	ShaderInit(const std::string& vertexFilePath, const std::string& fragmentFilePath);

	// compile shaders.
	GLuint	CompileShader(const std::string& filePath, unsigned int shaderType);

	// use shader
	void	Use()
	{
		glUseProgram(shaderProgram);
	}

	// checks max vertex att
	void	getMaxVertexAttribs()
	{
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &Attributes);
		std::cout << "Maximum numbers of vertex attributes supported: " << Attributes << std::endl;
	}


	// utility uniform functions
	void	setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
	}
	void	setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
	void	setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
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
