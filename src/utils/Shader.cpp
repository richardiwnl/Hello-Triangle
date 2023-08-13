#include "Shader.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::string vertexShaderCode{}, fragmentShaderCode{};
	std::ifstream vertexShaderFile{}, fragmentShaderFile{};

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);

		std::stringstream vertexShaderStream{}, fragmentShaderStream{};

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexShaderCode = vertexShaderStream.str();
		fragmentShaderCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure& err)
	{
		std::cerr << "[error] shader file not successfully read!\n";
		return;
	}

	const char* cVertexShaderCode{ vertexShaderCode.data() };

	unsigned int vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &cVertexShaderCode, NULL);
	glCompileShader(vertexShader);

	const char* cFragmentShaderCode{ fragmentShaderCode.data() };

	unsigned int fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &cFragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(ID);
}
