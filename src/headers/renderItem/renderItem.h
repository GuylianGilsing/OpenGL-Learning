#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RenderItem
{
private:
    // Keep this for the renderBatch class.
    // unsigned int vaoBuffer; // Used to draw multiple objects with the same vertexAttribPointer settings.
    // -----
    bool usesIndexedDrawing = false;

    unsigned int vboBuffer; // Used for vertex data.
    unsigned int eboBuffer; // Used for indexed rendering.

    // Render options.

    // The shape that is used when rendering.
    GLenum renderMode = GL_TRIANGLES;
    int renderOffset;

    GLsizei indexCount;
    GLenum indexType;
    GLvoid* indexOffset;

public:
    void setVertexData(float a_verteces[], GLenum a_drawType);
    void setIndexData(unsigned int a_indices[], GLenum a_drawType);
    void setDataLayout(int a_index, int a_size, bool a_normalized, GLenum a_type, GLsizei a_stride, GLvoid* a_pointer);
    
    void setNormalDrawingLayout(GLenum a_renderMode, int a_offset, GLsizei a_indexCount);
    void setIndexedDrawingLayout(GLenum a_renderMode, GLsizei a_indexCount, GLenum a_indexType, GLvoid* a_indexOffset);
    
    void render();
};