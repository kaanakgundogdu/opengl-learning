#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void init_window();
int creation_error();
void set_window_color(const GLFWwindow *window);
void close_delete_window(GLFWwindow *window);

const int window_width = 800;
const int window_height= 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\n\0";


const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.8,0.3f,0.02f,1.0);\n"

"}\n\0";


int main() {
	init_window();

	GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Kaan's OpenGL Test", NULL, NULL);

	if (window == NULL)
		return creation_error();
	
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, window_width, window_height);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



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


	GLuint VAO,VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	set_window_color(window);
	glfwSwapBuffers(window);


	while (!glfwWindowShouldClose(window))
	{
		set_window_color(window);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

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