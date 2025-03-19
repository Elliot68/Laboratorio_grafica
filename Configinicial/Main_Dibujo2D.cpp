//Practica 2				Alvarado Lucas Elliot	14/02/2025
//14 de febrero 2025			318265114

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "P2 EAL", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, resize);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // Datos de vértices: posición (x,y,z) y color (r,g,b)
    float vertices[] = {
        // Base de R2D2 (rectángulo)
        -0.4f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,
         0.4f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,
         0.4f,  0.2f, 0.0f,   1.0f, 1.0f, 1.0f,
        -0.4f,  0.2f, 0.0f,   1.0f, 1.0f, 1.0f,

        // Cúpula de R2D2 (triángulo superior)
        -0.4f, 0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
         0.4f, 0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
         0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,

         // Ojo de R2D2 (pequeño rectángulo en la cúpula)
         -0.05f, 0.3f, 0.0f,   0.0f, 0.0f, 0.0f,
          0.05f, 0.3f, 0.0f,   0.0f, 0.0f, 0.0f,
          0.05f, 0.35f, 0.0f,  0.0f, 0.0f, 0.0f,
         -0.05f, 0.35f, 0.0f,  0.0f, 0.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,       // Base
        4, 5, 6,               // Cúpula
        7, 8, 9, 9, 10, 7       // Ojo
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Configurar VAO, VBO y EBO
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atributo 0: posición (3 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Atributo 1: color (3 floats)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Bucle principal de renderizado
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();
        glBindVertexArray(VAO);
        // Usamos la cantidad correcta de índices
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
