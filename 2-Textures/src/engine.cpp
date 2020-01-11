#include "engine.h"

Engine::Engine(int a_width, int a_height, const char* a_windowName)
{
    this->screenWidth = a_width;
    this->screenHeight = a_height;
    this->windowName = a_windowName;
}

int Engine::Initialize()
{
    // Initialize GLFW.
    glfwInit();

    // Tell GLFW that we want to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Tell GLFW that we want to use the OpenGL's core profile.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Do this for mac compatability.
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create Window.

    // Instantiate the window object.
    this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, this->windowName, NULL, NULL);

    // Make sure that the window is created.
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();

        std::cin.get();
        return 0;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD.

    // Make sure that glad has been initialized successfully.
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        
        std::cin.get();
        return 0;
    }

    // Set the viewport

    glViewport(0, 0, this->screenWidth, this->screenHeight);

    // Setup callbacks.

    // Binds the 'framebuffer_size_callback' method to the window resize event.
    glfwSetFramebufferSizeCallback(window, WindowResize);

    this->SetupOpenGlRendering();

    // Start game loop.
    while(!glfwWindowShouldClose(this->window))
    {
        // Calculate the elapsed time between the current and previous frame.
        float m_frameTime = (float)glfwGetTime();
        float m_deltaTime = m_frameTime - this->lastFrameTime;
        this->lastFrameTime = m_frameTime;

        glfwPollEvents();
        this->ProcessInput(this->window);

        glClearColor(this->clearColor.x, this->clearColor.y, this->clearColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Application logic
        this->Update(m_deltaTime);
        this->Draw();

        glfwSwapBuffers(this->window);
    }

    glfwTerminate();

    return 1;
}

void WindowResize(GLFWwindow* a_window, int a_width, int a_height)
{
    glViewport(0, 0, a_width, a_height);

    // TODO: Do your resize logic here...
}

void Engine::ProcessInput(GLFWwindow* a_window)
{
    // TODO: Process your input here...

    // If the escape key gets pressed, close the window.
    if(glfwGetKey(a_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(a_window, true);
}

void Engine::SetupOpenGlRendering()
{
    // TODO: Setup OpenGL code here...

    // Setup shader.
    this->triangleShader.setVertexShader("src/shaders/basicVertexShader.glsl");
    this->triangleShader.setFragmentShader("src/shaders/basicFragmentShader.glsl");
    this->triangleShader.compile();

    this->triangleShader.use();

    // Setup triangle render code.
    glGenVertexArrays(1, &this->triangleVAO);
    glGenBuffers(1, &this->triangleVBO);

    glBindVertexArray(this->triangleVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), this->triangleVertexData,  GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(0); // Enable vertex pairs (vertices)
    glEnableVertexAttribArray(1); // Enable vertex colors
    glEnableVertexAttribArray(2); // Enable texture coordinates

    // Setup texturing.
    glGenTextures(1, &this->triangleTextureId);
    glBindTexture(GL_TEXTURE_2D, this->triangleTextureId);

    // Setup texture filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generate and load the texture.
    int m_width, m_height, m_nrChannels;
    unsigned char* m_textureImage = stbi_load("src/img/crabrave.jpg", &m_width, &m_height, &m_nrChannels, 0);

    if(m_textureImage)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_textureImage);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Could not load the texture." << std::endl;
    }

    stbi_image_free(m_textureImage);
}

void Engine::Update(float a_deltaTime)
{
    // TODO: Update your logic here...
}

void Engine::Draw()
{
    // TODO: Render your stuff here...
    glBindVertexArray(this->triangleVAO);
    glBindTexture(GL_TEXTURE_2D, this->triangleTextureId);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}