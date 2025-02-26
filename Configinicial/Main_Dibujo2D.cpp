//Practica 2					Alvarado Lucas Elliot	14/02/2025
//14 de febrero 2025			318265114

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "P2 EAL", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		-0.8f,  0.6f, 0.0f,    1.0f, 0.5f, 0.0f,  // bordes
		-0.54f, 0.438f, 0.0f,    1.0f, 0.5f, 0.0f,  // bordes
		-0.462f, 0.203f, 0.0f,   1.0f, 0.5f, 0.0f,  // bordes
		-0.37f,  0.2f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes 
		-0.359f,  0.193f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		-0.314f,  0.103f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		-0.717f,  -0.269f, 0.0f,   1.0f, 0.5f, 0.0f, //  bordes
		-0.378f,  -0.343f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.017f,  -0.724f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.432f,  -0.343f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.793f,  -0.263f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.390f,  0.065f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.455f,  0.251f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes 
		0.603f,  0.274f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.69f,  0.487f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.597f,  0.554f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.78f,  0.738f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.371f,  0.770f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes
		0.262f,  0.564f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes 
		-0.214f,  0.541f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes 
		-0.343f,  0.738f, 0.0f,   1.0f, 0.5f, 0.0f, // bordes

		-0.314f,  0.103f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo izquierdo
		-0.517f,  -0.186f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo izquierdo
		-0.378f,  -0.343f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo izquierdo
		0.017f,  -0.724f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo izquierdo

		0.390f,  0.065f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo derecho
		0.597f,  -0.173f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo derecho
		0.432f,  -0.343f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo derecho 
		0.017f,  -0.724f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo derecho
		
		0.455f,  0.251f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo interior
		0.526f,  0.413f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo interior
		-0.427f,  0.416f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo interior
		-0.359f,  0.193f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo interior
		-0.314f,  0.103f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo interior
		0.017f,  -0.724f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo interior
		0.390f,  0.065f, 0.0f,   1.0f, 0.5f, 0.0f, // triangulo interior
	
		-0.226f,  -0.334f, 0.0f,   1.0f, 0.5f, 0.0f, // ojo izquierdo
		-0.226f,  -0.428f, 0.0f,   1.0f, 0.5f, 0.0f, // ojo izquierdo
		-0.147f,  -0.426f, 0.0f,   1.0f, 0.5f, 0.0f, // ojo izquierdo
		-0.166f,  -0.338f, 0.0f,   1.0f, 0.5f, 0.0f, // ojo izquierdo

		0.212f,  -0.353f, 0.0f,   1.0f, 0.5f, 0.0f, // ojo derecho
		0.214f,  -0.419f, 0.0f,   1.0f, 0.5f, 0.0f, // ojo derecho 
		0.292f,  -0.415f, 0.0f,   1.0f, 0.5f, 0.0f, // ojo derecho
		0.288f,  -0.343f, 0.0f,   1.0f, 0.5f, 0.0f, // ojo derecho

		




	};
	unsigned int indices[] = {  // note that we start from 0!
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,
		// second Triangle
		
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(50);
        //glDrawArrays(GL_POINTS,0,4);
        
        //glDrawArrays(GL_LINES,0,9);
        glDrawArrays(GL_LINE_LOOP,0,21);
		glDrawArrays(GL_LINE_LOOP,21,4);
		glDrawArrays(GL_LINE_LOOP, 25, 4);
		glDrawArrays(GL_LINE_LOOP, 29, 7);
		glDrawArrays(GL_LINE_LOOP, 36, 4);
		glDrawArrays(GL_LINE_LOOP, 40, 4);
        
        //glDrawArrays(GL_TRIANGLES,1,3);
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}