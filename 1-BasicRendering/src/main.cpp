// Includes the standard "std" lib
#include <iostream>

// Include libs.
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "classes\shader\shader.h"


float screenWidth = 640.0f;
float screenHeight = 480.0f;

// Objects.
Shader basicShaderProgram;

// References.
void framebuffer_size_callback(GLFWwindow* a_window, int a_width, int a_height);
void processInput(GLFWwindow* a_window);
void getError(int a_line);

int main()
{
    // ---
    // Initialize GLFW.
    // ---
    glfwInit();

    // Tell GLFW that we want to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Tell GLFW that we want to use the OpenGL's core profile.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Do this for mac compatability.
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // ---
    // Create Window.
    // ---

    // Instantiate the window object.
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);

    // Make sure that the window is created.
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();

        std::cin.get();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // ---
    // Initialize GLAD.
    // ---

    // Make sure that glad has been initialized successfully.
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        
        std::cin.get();
        return -1;
    }

    // ---
    // Set the viewport
    // ---

    glViewport(0, 0, screenWidth, screenHeight);

    // ---
    // Setup callbacks.
    // ---

    // Binds the 'framebuffer_size_callback' method to the window resize event.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ---
    // Setup rendering.
    // ---

    unsigned int shaderProgram;

    basicShaderProgram.setVertexShader("src/shaders/basicVertexShader.glsl");
    basicShaderProgram.setFragmentShader("src/shaders/basicFragmentShader.glsl");

    shaderProgram = basicShaderProgram.compile();
    basicShaderProgram.use();

    // Set the rectangle color.
    int colorUniform = basicShaderProgram.getUniformLocation("u_Color");
    glUniform4f(colorUniform, 1.0f, 0.2f, 0.3f, 1.0f);

    // Set the matrix in pixel space, so 1px = to 1px.
    int matrixUniform = basicShaderProgram.getUniformLocation("u_MVP");
    glm::mat4 proj = glm::ortho(0.0f, 320.0f * (screenWidth/screenHeight), 0.0f, 320.0f * (screenWidth/screenHeight), -1.0f, 1.0f);
    glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, &proj[0][0]);

    float vertices[] = {
        // Triangle 1
        0.0f, 0.0f, 0.0f, 0.0f, // Index 0
        0.0f, 100.0f, 0.0f, 0.0f, // Index 1
        100.0f, 100.0f, 0.0f, 0.0f, // Index 2
         
         // Triangle 2
        100.0f, 0.0f, 0.0f, 0.0f,  // Index 3
    };

    unsigned int indices[] = {
        // // Triangle 1
        0, 1, 2,

        // // Triangle 2
        0, 3, 2
        // 0,0,0,0,0,0
    };

    unsigned int renderVao;
    unsigned int vboBuffer;
    unsigned int eboBuffer;

    // Rendering steps:
    // 1. Create a vao with glGenVertexArrays and then bind it with glBindVertexArray.
    // 2. Create a vbo.
    // 3. Set vertex attribute pointers.
    // 4. enable vertex attribute pointers.
    // 5. Render.

    // Create a vao.
    glGenVertexArrays(1, &renderVao);
    glBindVertexArray(renderVao);

    // Create a vbo and fill it with data.
    glGenBuffers(1, &vboBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_TRUE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &eboBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Application Loop.
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Start rendering.
        basicShaderProgram.use();
        glBindVertexArray(renderVao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        // End rendering.
        
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

// ---
// Callback logic.
// ---

// Handle window resize.
void framebuffer_size_callback(GLFWwindow* a_window, int a_width, int a_height)
{
    glViewport(0, 0, a_width, a_height);

    // Set the matrix in pixel space, so 1px = to 1px.
    int matrixUniform = basicShaderProgram.getUniformLocation("u_MVP");
    glm::mat4 proj = glm::ortho(0.0f, (float)a_width * (a_width/a_height), 0.0f, (float)a_height * (a_width/a_height), -1.0f, 1.0f);
    glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, &proj[0][0]);
}

void processInput(GLFWwindow* a_window)
{
    // If the escape key gets pressed, close the window.
    if(glfwGetKey(a_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(a_window, true);
}

void getError(int a_line)
{
    GLenum m_error = glGetError();

    if(m_error != GL_NO_ERROR)
        std::cout << m_error << " At line: " << a_line << std::endl;
}