#include "geng.hpp"

std::string	ShaderInit::readShaderSource(const	std::string& filepath)
{
	std::ifstream file(filepath);
	if (!file)
	{
		throw std::runtime_error("Failed to open shader file: " + filepath);
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint	ShaderInit::make_module(const std::string& filepath, unsigned int module_type)
{
		std::string shaderSource = readShaderSource(filepath);
		const char* source = shaderSource.c_str();

		GLuint shaderModule = glCreateShader(module_type);
		glShaderSource(shaderModule, 1, &source, nullptr);
		glCompileShader(shaderModule);

		GLint compileStatus;
		glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderModule, sizeof(infoLog), nullptr, infoLog);
			glDeleteShader(shaderModule); // Ensure we don't leak the shader module.
			throw std::runtime_error("Shader compilation error in " + filepath + ":\n" + infoLog);
		}
	return shaderModule;
}

unsigned	int	ShaderInit::make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath)
{
	GLint linkStatus;
	GLuint vertexShader = make_module(vertex_filepath, GL_VERTEX_SHADER);
	GLuint fragmentShader = make_module(fragment_filepath, GL_FRAGMENT_SHADER);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Delete shaders after linking them into the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		GLchar	infoLog[1024];
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
		glDeleteProgram(shaderProgram); // Ensure we don't leak the shader program.
		throw std::runtime_error(std::string("Shader linking error:\n") + infoLog);
	}
	return shaderProgram;
}
