#include <GLFW/glfw3.h>
#include <glad/glad.h>

class RenderItem
{
private:
    unsigned int vboBuffer; // Used for vertex data.
    unsigned int vaoBuffer; // Used to draw multiple objects with the same vertexAttribPointer settings.
    unsigned int eboBuffer; // Used for indexed rendering.
};