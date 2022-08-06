#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void init_window();
int creation_error();
void set_window_color(const GLFWwindow *window);
void close_delete_window(GLFWwindow *window);

const int window_width = 800;
const int window_height= 800;


GLfloat vertices[] = {
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,// LOVER LEFT
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // LOWER RIGHT
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //UPPER CORNER
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // INNER LEFT
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // INNER RIGHT
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, // INNER DOWN
};

GLuint indices[] = {
	0,3,5,
	3,2,4,
	5,4,1
};

int main() {
	init_window();

	GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Kaan's OpenGL Test", NULL, NULL);

	if (window == NULL)
		return creation_error();
	
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, window_width, window_height);


	Shader shaderProgram("default.vert", "default.frag");


	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(vertices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		set_window_color(window);
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	close_delete_window(window);
	return 0;
}

void init_window() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

int creation_error() {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return -1;
}

void set_window_color( const GLFWwindow *window) {

	glClearColor(.07f, .13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void close_delete_window(GLFWwindow *window) {

	glfwDestroyWindow(window);
	glfwTerminate();
}