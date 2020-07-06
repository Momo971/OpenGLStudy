// OpenGLTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float firstVertices[] = {
	0.3f, 0.5f, 0.0f,
	-0.2f, 0.0f, 0.0f,
	0.3f, -0.5f, 0.0f,
};

float secondVertices[] = {
	-0.3f, 0.5f, 0.0f,
	0.2f, 0.0f, 0.0f,
	-0.3f, -0.5f, 0.0f,
};

unsigned int indices[] = {
	0, 1, 2,
	3, 4, 2
};

unsigned int VAO;
unsigned int VBO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
unsigned int EBO;

const char* vertexShaderStr = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0f);\n"
"}\0";

const char* fragmentShaderStrA = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 outColor;\n"
"void main()\n"
"{\n"
"	FragColor = outColor;\n"
"}\0";



int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);


	//创建顶点着色器
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderStr, NULL);
	glCompileShader(vertexShader);

	//创建
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderStrA, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//着色器程序
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//shaderProgram[1] = glCreateProgram();
	//glAttachShader(shaderProgram[1], vertexShader);
	//glAttachShader(shaderProgram[1], fragmentShader[1]);
	//glLinkProgram(shaderProgram[1]);

	//链接后就可以删除
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//glDeleteShader(fragmentShader[1]);

	//激活程序对象
	glUseProgram(shaderProgram);
	//glUseProgram(shaderProgram[1]);


	glGenVertexArrays(2, &VAO);
	glGenBuffers(2, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertices), firstVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glBindVertexArray(VAO[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);




	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


//窗口大小变动时，视口随之变换。
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
