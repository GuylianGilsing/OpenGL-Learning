// Include libs.
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "headers\shader\shader.h"

// Includes the standard "std" lib
#include <iostream>

int screenWidth = 800;
int screenHeight = 600;

// Objects.
Shader basicShaderProgram;

// References.
void framebuffer_size_callback(GLFWwindow* a_window, int a_width, int a_height);
void processInput(GLFWwindow* a_window);
int setupRender();
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

    // // Setup the rendering.
    // if(!setupRender())
    // {
    //     std::cout << "Rendering setup failed!." << std::endl;
    //     std::cin.get();
    //     return -1;
    // }
    unsigned int shaderProgram;

    basicShaderProgram.setVertexShader("src/shaders/basicVertexShader.glsl");
    basicShaderProgram.setFragmentShader("src/shaders/basicFragmentShader.glsl");

    shaderProgram = basicShaderProgram.compile();
    basicShaderProgram.use();

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    // Application Loop.
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Start rendering.
        // draw our first triangle
        basicShaderProgram.use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
        // render();
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

// ---
// Rendering
// ---

// The vertices for rendering a triangle.
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

// In order to use the vertex and fragment shader, we need to link those to a shader program.
unsigned int shaderProgram;
unsigned int vaoBuffer;

// Handles the data we want to use for the rendering of the triangle.
int setupRender()
{
    // ---
    // Create a new Vertex Buffer Object. (VBO)
    // ---

    // Integer used to keep track of the vertex buffers.
    unsigned int vboBuffer;

    // Generate and bind a new vertex buffer object (VBO).
    glGenBuffers(1, &vboBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);

    // we can give this newly created VBO data as long as it's bound.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // ---
    // Create a shader program. (GLSL)
    // ---

    basicShaderProgram.setVertexShader("src/shaders/basicVertexShader.glsl");
    basicShaderProgram.setFragmentShader("src/shaders/basicFragmentShader.glsl");

    shaderProgram = basicShaderProgram.compile();
    basicShaderProgram.use();

    // ---
    // Linking vertex attributes.
    // ---

    // The vertex shader allows us to specify any input we want in the form of vertex attributes and while 
    // this allows for great flexibility, it does mean we have to manually specify what part of our input 
    // data goes to which vertex attribute in the vertex shader. 
    // This means we have to specify how OpenGL should interpret the vertex data before rendering.
    //
    // - The position data is stored as 32-bit (4 byte) floating point values.
    // - Each position is composed of 3 of those values.
    // - There is no space (or other values) between each set of 3 values. The values are tightly packed in the array.
    // - The first value in the data is at the beginning of the buffer.
    // 
    // - https://learnopengl.com/Getting-started/Hello-Triangle

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // The function glVertexAttribPointer has quite a few parameters so let's carefully walk through them.
    //
    // - The first parameter specifies which vertex attribute we want to configure. 
    //   Remember that we specified the location of the position vertex attribute in the vertex 
    //   shader with layout (location = 0). This sets the location of the vertex attribute to 0 and 
    //   since we want to pass data to this vertex attribute, we pass in 0.
    //
    // - The next argument specifies the size of the vertex attribute. 
    //   The vertex attribute is a vec3 so it is composed of 3 values.
    //
    // - The third argument specifies the type of the data which is GL_FLOAT 
    //   (a vec* in GLSL consists of floating point values).
    //
    // - The next argument specifies if we want the data to be normalized. 
    //   If we're inputting integer data types (int, byte) and we've set this to GL_TRUE, 
    //   the integer data is normalized to 0 (or -1 for signed data) and 1 when converted to float. 
    //   This is not relevant for us so we'll leave this at GL_FALSE.
    //
    // - The fifth argument is known as the stride and tells us the space between consecutive vertex attributes. 
    //   Since the next set of position data is located exactly 3 times the size of a float away we specify 
    //   that value as the stride. Note that since we know that the array is tightly packed 
    //   (there is no space between the next vertex attribute value) we could've also specified the 
    //   stride as 0 to let OpenGL determine the stride (this only works when values are tightly packed). 
    //   Whenever we have more vertex attributes we have to carefully define the spacing between each vertex 
    //   attribute but we'll get to see more examples of that later on.
    //
    // - The last parameter is of type void* and thus requires that weird cast. 
    //   This is the offset of where the position data begins in the buffer. 
    //   Since the position data is at the start of the data array this value is just 0. 
    //   We will explore this parameter in more detail later on
    //
    // Each vertex attribute takes its data from memory managed by a VBO and which VBO it takes its data from 
    // (you can have multiple VBOs) is determined by the VBO currently bound to GL_ARRAY_BUFFER when calling 
    // glVertexAttribPointer. Since the previously defined VBO is still bound before 
    // calling glVertexAttribPointer vertex attribute 0 is now associated with its vertex data.

    // We have to repeat this process every time we want to draw an object. 
    // It may not look like that much, but imagine if we have over 5 vertex attributes and perhaps 
    // 100s of different objects (which is not uncommon). Binding the appropriate buffer objects 
    // and configuring all vertex attributes for each of those objects quickly becomes a cumbersome process. 
    // What if there was some way we could store all these state configurations into an object and simply 
    // bind this object to restore its state?

    // ---
    // Generate a Vertex Array Object
    // ---

    // A vertex array object (also known as VAO) can be bound just like a vertex buffer object and any 
    // subsequent vertex attribute calls from that point on will be stored inside the VAO. 
    // This has the advantage that when configuring vertex attribute pointers you only have to make those 
    // calls once and whenever we want to draw the object, we can just bind the corresponding VAO. 
    // This makes switching between different vertex data and attribute configurations as easy as binding a 
    // different VAO. All the state we just set is stored inside the VAO.
    //
    // WARNING:
    // Core OpenGL requires that we use a VAO so it knows what to do with our vertex inputs. 
    // If we fail to bind a VAO, OpenGL will most likely refuse to draw anything.

    // vaoBuffer is defined above this function.
    glGenVertexArrays(1, &vaoBuffer);

    // Initialization code (done once (unless your object frequently changes))
    // 1. Bind Vertex Array Object.
    glBindVertexArray(vaoBuffer);

    // 2. Copy vertices array into a buffer.
    glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. Set vertex attributes pointers.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return 1;
}

void render()
{
    // glUseProgram(shaderProgram);
    basicShaderProgram.use();
    glBindVertexArray(vaoBuffer);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
}