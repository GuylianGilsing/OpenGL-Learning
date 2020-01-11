#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../shader/shader.h"

class Mesh
{
private:
    unsigned int vboBuffer;
    unsigned int vaoBuffer;
    unsigned int iboBuffer;

    glm::vec3 *vertices;
    unsigned int *indices;

    Shader shaderprogram;

public:
    void setVertexData(glm::vec3 a_vertices[]);
};