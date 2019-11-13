// Include libs.
#include "dependencies\GLAD\src\glad.c"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

// Includes the standard "std" lib
#include <iostream>

int screenWidth = 800;
int screenHeight = 600;

// References.
void framebuffer_size_callback(GLFWwindow* a_window, int a_width, int a_height);
void processInput(GLFWwindow* a_window);
void render();

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

    // Application Loop.
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput(window);

        // Start rendering.

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        render();
        glClear(GL_COLOR_BUFFER_BIT);

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
}

void processInput(GLFWwindow* a_window)
{
    // If the escape key gets pressed, close the window.
    if(glfwGetKey(a_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(a_window, true);
}

void render()
{
    // Do render stuff :)
}