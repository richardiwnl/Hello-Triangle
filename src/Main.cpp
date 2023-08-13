#include <iostream>

#include "utils/Shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr int SCREEN_WIDTH{ 640 };
constexpr int SCREEN_HEIGHT{ 480 };

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{

	if (!glfwInit())
	{
		std::cerr << "[error] failed to initialize GLFW\n";
		return -1;
	}

	// Setting GLFW window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating the window
	GLFWwindow* window{ glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Triangle", NULL, NULL) };

	if (!window)
	{
		std::cerr << "[error] failed to create the GLFW window!\n";
		glfwTerminate();
		return -1;
	}

	// Making the context of our window the current context
	glfwMakeContextCurrent(window);

	// Initializing glad
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "[error] failed to initialize GLAD\n";
		glfwTerminate();
		return -1;
	}

	// Setting the framebuffer size callback
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	std::cout << "Being rendered on: " << glGetString(GL_RENDERER) << '\n';

	Shader ourShader{ R"(src\shaders\vertexShader.glsl)", R"(src\shaders\fragmentShader.glsl)" };

	float vertices[] = {
		// X		// Y		// Z
		-0.5f,		-0.5f,		0.0f,
		 0.5f,		-0.5f,		0.0f,
		 0.0f,		 0.5f,		0.0f,
	};

	float colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	unsigned int VAO{};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int vertexBuffer{};
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	unsigned int colorBuffer{};
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(1);

	ourShader.use();

	while (!glfwWindowShouldClose(window))
	{
		// Handle input
		processInput(window);

		// Render things
		glClearColor(30.0f / 255, 30.0f / 255, 30.0f / 255, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	static bool spaceKeystrokeLock{ false };

	if (!glfwGetKey(window, GLFW_KEY_SPACE))
	{
		spaceKeystrokeLock = false;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) && !spaceKeystrokeLock)
	{
		int currentMode{};
		glGetIntegerv(GL_POLYGON_MODE, &currentMode);

		glPolygonMode(GL_FRONT_AND_BACK, currentMode == GL_FILL ? GL_LINE : GL_FILL);

		spaceKeystrokeLock = true;
	}
}
