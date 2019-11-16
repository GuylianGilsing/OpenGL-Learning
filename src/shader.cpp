#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "headers/shader/shader.h"

// Sets the vertex shader of this program.
bool Shader::setVertexShader(std::string a_vertexShaderSource)
{
    this->vertexShaderSource = a_vertexShaderSource.c_str();

    // Create the new vertex shader.
    this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    // Add the shader code to the shader.
    glShaderSource(this->vertexShaderID, 1, &this->vertexShaderSource, NULL);
    glCompileShader(this->vertexShaderID);

    if(!this->shaderCompiled(this->vertexShaderID))
        return false;

    return true;
}

bool Shader::setFragmentShader(std::string a_fragmentShaderSource)
{
    this->fragmentShaderSource = a_fragmentShaderSource.c_str();

    // Create the new vertex shader.
    this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Add the shader code to the shader.
    glShaderSource(this->fragmentShaderID, 1, &this->fragmentShaderSource, NULL);
    glCompileShader(this->fragmentShaderID);

    if(!this->shaderCompiled(this->fragmentShaderID))
        return false;

    return true;
}

int Shader::compile()
{
    this->shaderProgram = glCreateProgram();

    // Attach the vertex and fragment shader.
    glAttachShader(this->shaderProgram, this->vertexShaderID);
    glAttachShader(this->shaderProgram, this->fragmentShaderID);
    
    // Compile the shader.
    glLinkProgram(this->shaderProgram);

    int compiled;
    char infoLog[512];

    // Get the compile status.
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &compiled);

    if(!compiled)
    {
        glGetShaderInfoLog(this->shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR: Could not compile shader program: " << infoLog << std::endl; 
    
        return -1;
    }

    // Delete the shaders.
    glDeleteShader(this->vertexShaderID);
    glDeleteShader(this->fragmentShaderID);

    return this->shaderProgram;
}

void Shader::use()
{
    glUseProgram(this->shaderProgram);
}

bool Shader::shaderCompiled(unsigned int a_id)
{
    int compiled;
    char infoLog[512];

    // Get the compile status.
    glGetShaderiv(a_id, GL_COMPILE_STATUS, &compiled);

    if(!compiled)
    {
        glGetShaderInfoLog(a_id, 512, NULL, infoLog);
        std::cerr << "ERROR: Could not compile shader: " << infoLog << std::endl; 
    
        return false;
    }

    return true;
}