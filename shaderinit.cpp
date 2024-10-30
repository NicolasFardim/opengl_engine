#include "geng.hpp"

std::string	ShaderInit::readShaderSource(const	std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file)
	{
		throw std::runtime_error("Failed to open shader file: " + filePath);
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint	ShaderInit::CompileShader(const std::string& filePath, unsigned int shaderType)
{
		std::string readSource = readShaderSource(filePath);
		const char* shaderSource = readSource.c_str();

		GLuint shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &shaderSource, nullptr);
		glCompileShader(shaderID);

		GLint compileStatus;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
			glDeleteShader(shaderID); // Ensure any leak.
			throw std::runtime_error("ERROR::SHADER::COMPILATION_FAILED\n " + filePath + ":\n" + infoLog);
		}
	return shaderID;
}

ShaderInit::ShaderInit(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	GLint linkStatus;
	GLuint vertexShader = CompileShader(vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentFilePath, GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();
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
		throw std::runtime_error(std::string("ERROR::SHADER::LINKING_FAILED\n") + infoLog);
	}
}
