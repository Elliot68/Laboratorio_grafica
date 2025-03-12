/*Tarea7								Alvarado Lucas Elliot
Fecha de entrega: 10 de marzo 2025 					3182655117
*/

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f,
codo = 0.0f,
muneca = 0.0f,
dedo1=0.0f,
dedo2=0.0f,
dedo3 = 0.0f,

dedo1B = 0.0f,
dedo2B = 0.0f,
dedo3B = 0.0f,

dedo1C = 0.0f,
dedo2C = 0.0f,
dedo3C = 0.0f,

dedo1D = 0.0f,
dedo2D = 0.0f,
dedo3D = 0.0f,

dedo1E = 0.0f,
dedo2E = 0.0f,
dedo3E = 0.0f;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Tarea 7 Elliot Alvarado Lucas", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection


	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		-0.5f,  0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		
	    -0.5f, -0.5f,-0.5f, 
		 0.5f, -0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
	    -0.5f,  0.5f,-0.5f, 
	    -0.5f, -0.5f,-0.5f, 
		
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,
      
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



		//View set up 
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	

		glBindVertexArray(VAO);
		
		//Model bicep
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.5f, 2.0f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		//model antebrazo
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0, 0.0f));
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.5f, 2.0f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		//model palma
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.25, 0.0f));
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0, 0.0f));
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 2.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		glm::mat4 palmaModel = modelTemp2;

		//modelo dedo A1
		model = glm::translate(palmaModel, glm::vec3(0.25f, 0.85f, 0.875f));
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.75f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D

		//modelo dedo B2
		model = glm::translate(modelTemp, glm::vec3(0.75f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3( 0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//modelo dedo C3
		model = glm::translate(modelTemp, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.3f, 0.25f));
		color = glm::vec3(9.0f, 2.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E
		//--------------------------------------------------------------------------------
		//modelo dedo A2
		model = glm::translate(palmaModel, glm::vec3(0.25f, 0.85f, 0.3f));
		model = glm::rotate(model, glm::radians(dedo1B), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.75f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D

		//modelo dedo B2
		model = glm::translate(modelTemp, glm::vec3(0.75f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2B), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//modelo dedo C2
		model = glm::translate(modelTemp, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3B), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.3f, 0.25f));
		color = glm::vec3(9.0f, 2.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E
		//*------------------------------------------------------------------------------------
		//modelo dedo A3
		model = glm::translate(palmaModel, glm::vec3(0.25f, 0.85f, -0.275f));
		model = glm::rotate(model, glm::radians(dedo1C), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.75f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D

		//modelo dedo B3
		model = glm::translate(modelTemp, glm::vec3(0.75f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2C), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//modelo dedo C3
		model = glm::translate(modelTemp, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3C), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.3f, 0.25f));
		color = glm::vec3(9.0f, 2.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E
		//*------------------------------------------------------------------------------------
		//modelo dedo A4
		model = glm::translate(palmaModel, glm::vec3(0.25f, 0.85f, -0.85f));
		model = glm::rotate(model, glm::radians(dedo1D), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.75f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D

		//modelo dedo B4
		model = glm::translate(modelTemp, glm::vec3(0.75f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2D), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//modelo dedo C4
		model = glm::translate(modelTemp, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3D), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.3f, 0.25f));
		color = glm::vec3(9.0f, 2.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E
		//*------------------------------------------------------------------------------------
		//modelo dedo A5
		model = glm::translate(palmaModel, glm::vec3(0.25f, -0.3f, 0.875f));
		model = glm::rotate(model, glm::radians(dedo1E), glm::vec3(0.0f, -1.0, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D

		//modelo dedo B5
		model = glm::translate(modelTemp, glm::vec3(0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2E), glm::vec3(0.0f, -1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		
		



		glBindVertexArray(0);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX -= 0.02f;
	 if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.06f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.06f;
	 if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		 hombro += 0.05f;
		if (hombro < -100.0f) hombro = -100.0f;
		if (hombro > 90.0f) hombro = 90.0f;
	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		 hombro -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		 codo += 0.05f;
		if (codo< -90.0f) codo = -90.0f;
		if (codo > 0.0f) codo = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		 codo -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		 muneca += 0.05f;
		if (muneca < -90.0f) muneca = -90.0f;
		if (muneca > 45.0f) muneca = 45.0f;
	 if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		 muneca-= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		 dedo1 += 0.05f;
		if (dedo1 < 0.0f) dedo1 = 0.0f;
		if (dedo1 > 90.0f) dedo1 = 90.0f;
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		 dedo1 -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		 dedo2 += 0.05f;
		if (dedo2 < -90.0f) dedo2 = -90.0f;
		if (dedo2 > 0.0f) dedo2 = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		 dedo2 -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		 dedo3 += 0.05f;
	 if (dedo3 < -100.0f) dedo3 = -100.0f;
	 if (dedo3 > 0.0f) dedo3 = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		 dedo3 -= 0.05f;
	 //****************
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		 dedo1B += 0.05f;
	 if (dedo1B < 0.0f) dedo1B = 0.0f;
	 if (dedo1B > 90.0f) dedo1B = 90.0f;
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		 dedo1B -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		 dedo2B += 0.05f;
	 if (dedo2B < -90.0f) dedo2B = -90.0f;
	 if (dedo2B > 0.0f) dedo2B = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		 dedo2B -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		 dedo3B += 0.05f;
	 if (dedo3B < -100.0f) dedo3B = -100.0f;
	 if (dedo3B > 0.0f) dedo3B = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		 dedo3B -= 0.05f;
	 //****************
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		 dedo1C += 0.05f;
	 if (dedo1C < 0.0f) dedo1C = 0.0f;
	 if (dedo1C > 90.0f) dedo1C = 90.0f;
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		 dedo1C -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		 dedo2C += 0.05f;
	 if (dedo2C < -90.0f) dedo2C = -90.0f;
	 if (dedo2C > 0.0f) dedo2C = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		 dedo2C -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		 dedo3C += 0.05f;
	 if (dedo3C < -100.0f) dedo3C = -100.0f;
	 if (dedo3C > 0.0f) dedo3C = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		 dedo3C -= 0.05f;
	 //****************
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		 dedo1D += 0.05f;
	 if (dedo1D < 0.0f) dedo1D = 0.0f;
	 if (dedo1D > 90.0f) dedo1D = 90.0f;
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		 dedo1D -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		 dedo2D += 0.05f;
	 if (dedo2D < -90.0f) dedo2D = -90.0f;
	 if (dedo2D > 0.0f) dedo2D = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		 dedo2D -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		 dedo3D += 0.05f;
	 if (dedo3D < -100.0f) dedo3D = -100.0f;
	 if (dedo3D > 0.0f) dedo3D = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		 dedo3D -= 0.05f;
	 //****************
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		 dedo1E += 0.05f;
	 if (dedo1E < -40.0f) dedo1E= -40.0f;
	 if (dedo1E > 90.0f) dedo1E = 90.0f;
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		 dedo1E -= 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		 dedo2E += 0.05f;
	 if (dedo2E < -90.0f) dedo2E = -90.0f;
	 if (dedo2E > 0.0f) dedo2E = 0.0f;
	 if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		 dedo2E -= 0.05f;
	 
	 
 }


