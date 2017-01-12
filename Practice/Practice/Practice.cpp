/*
* Practice.cpp
*
* Copyright 2017  <Daniel Grimshaw>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*
*
*/
// OpenGL
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Standard Libraries
#include <iostream>
#include <cstdbool>

// Header Files
#include "util.h"
#include "Shader.h"
#include "Program.h"

// Functions

// Handlers
void key_handler(GLFWwindow * window, int key, int scancode, int action, int mode); // Keyboard driver
void button_handler(GLFWwindow * window, int button, int action, int mods); // Mouse button handler
void mouse_handler(GLFWwindow * window, double x, double y); // Mouse motion handler

// Filenames
std::string vertex_name = "vert.glsl";
std::string fragment_name = "frag.glsl";

// FPS Counter
double lastTime = 0;
int nbFrames = 0;

// Shaders
Shader vertex = Shader(GL_VERTEX_SHADER, vertex_name);
Shader fragment = Shader(GL_FRAGMENT_SHADER, fragment_name);

// Programs
Program shaders = Program(vertex, fragment);

// Buffer Objects
GLuint VBO, VAO, EBO;

// Uniforms

// Others
GLboolean neg = false;

// Controls
const char * controls = "\t\t\tShader Practice\r\n"
"Move the mouse to change the speed of the lines.\r\n"
"Further left increases density, right decreases density\r\n"
"down increases speed, and up decreases speed.\r\n"
"Click any mouse button to switch the direction of motion\r\n"
"Press the \'c\' key to show the cursor while over the window\r\n"
"and the \'h\' key to rehide it. Press \'q\' or ESC to exit.\r\n\0";

int main(int argc, char ** argv) {
	using namespace std;
	
	GLfloat vertices[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	
	// Display controls
	cout << controls << endl;

	// Initialize GLFW

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow * window = glfwCreateWindow(800, 600, "Practice", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Unable to create GLFW window\naborting ..." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_handler);
	glfwSetMouseButtonCallback(window, button_handler);
	glfwSetCursorPosCallback(window, mouse_handler);
	
	// Load all library function pointers

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) { // Doesn't run without GLEW
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    } 

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// Create Shaders
	vertex.create();
	fragment.create();

	// Create Programs
	shaders.create();

	glUseProgram(shaders.getId());

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	
	glViewport(0,0,width,height); // Tell GPU where to draw to and window size

	lastTime = glfwGetTime();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSwapInterval(0);

	GLint uniform_loc;

	uniform_loc = glGetUniformLocation(shaders.getId(), "u_time");
	glUniform1f(uniform_loc, (float)glfwGetTime());

	uniform_loc = glGetUniformLocation(shaders.getId(), "u_resolution");
	glUniform2f(uniform_loc, (float)width, (float)height);

	uniform_loc = glGetUniformLocation(shaders.getId(), "u_mouse");
	glUniform2f(uniform_loc, 0.0f, 0.0f);

	while (!glfwWindowShouldClose(window)) { // Callback loop
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaders.getId());

		uniform_loc = glGetUniformLocation(shaders.getId(), "u_time");
		glUniform1f(uniform_loc, (float)glfwGetTime());

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

		double currentTime = glfwGetTime();
		double deltaT = currentTime - lastTime;
		nbFrames++;
		if (deltaT >= 1){
			cout << 1.0 / (double)nbFrames << " ms/frame (" << nbFrames << " fps)" << endl;
			nbFrames = 0;
			lastTime = currentTime;
		}
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void key_handler(GLFWwindow * window, int key, int scancode, int action, int mode) {
	using namespace std;
	GLfloat speed = 0.1f;

	switch (key) { // Keyboard
	case GLFW_KEY_ESCAPE: // ESC
	case 'q':
	case 'Q': // Quit
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case 'w':
	case 'W':
		break;
	case 's':
	case 'S':
		break;
	case 'a':
	case 'A':
		break;
	case 'd':
	case 'D':
		break;
	case 'c':
	case 'C':
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	case 'h':
	case 'H':
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	default: // No key was pressed that is of importance
		break;
	}
}

void button_handler(GLFWwindow * window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			neg = !neg;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			neg = !neg;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			neg = !neg;
			break;
		}
	}
}

void mouse_handler(GLFWwindow * window, double x, double y) {
	GLint uniform_loc;

	uniform_loc = glGetUniformLocation(shaders.getId(), "u_mouse");
	if (neg) {
		glUniform2f(uniform_loc, (float)x, (float)y);
	}
	else {
		glUniform2f(uniform_loc, (float)x, (float)-y);
	}
}
