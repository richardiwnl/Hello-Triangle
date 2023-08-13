#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <string_view>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID{};

	Shader(const char* vertexShaderPath, const char* framentShaderPath);

	void use();

	void setBool(const std::string_view name, bool value) const;
	void setInt(const std::string_view name, int value) const;
	void setFloat(const std::string_view name, float value) const;

private:
	void checkCompileErrors(unsigned int shader, std::string_view type);
};

#endif