// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// #include "headers/renderItem/renderItem.h"

// void RenderItem::setVertexData(float a_vertices[], GLenum a_drawType)
// {
//     // Create the buffer.
//     glGenBuffers(1, &this->vboBuffer);
//     glBindBuffer(GL_VERTEX_ARRAY, this->vboBuffer);
    
//     // Insert data into the buffer.
//     glBufferData(GL_ARRAY_BUFFER, sizeof(a_vertices), a_vertices, a_drawType);
// }

// void RenderItem::setIndexData(unsigned int a_indices[], GLenum a_drawType)
// {
//     // Turn on indexed drawing for the render call.
//     if(!this->usesIndexedDrawing)
//         this->usesIndexedDrawing = true;

//     // Create the buffer.
//     glGenBuffers(1, &this->eboBuffer);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboBuffer);
    
//     // Insert data into the buffer.
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(a_indices), a_indices, a_drawType);
// }

// void RenderItem::setDataLayout(int a_index, int a_size, bool a_normalized, GLenum a_type, GLsizei a_stride, GLvoid* a_pointer)
// {
//     glVertexAttribPointer(a_index, a_size, a_type, a_normalized, a_stride, a_pointer);
// }

// void RenderItem::setNormalDrawingLayout(GLenum a_renderMode, int a_offset, GLsizei a_indexCount)
// {
//     this->renderMode = a_renderMode;
//     this->renderOffset = a_offset;
//     this->indexCount = a_indexCount;
// }

// void RenderItem::setIndexedDrawingLayout(GLenum a_renderMode, GLsizei a_indexCount, GLenum a_indexType, GLvoid* a_indexOffset)
// {
//     this->renderMode = a_renderMode;
//     this->indexCount = a_indexCount;
//     this->indexType = a_indexType;
//     this->indexOffset = a_indexOffset;
// }

// void RenderItem::render()
// {
//     if(this->usesIndexedDrawing)
//     {
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboBuffer);
//         glDrawElements(this->renderMode, this->indexCount, this->indexType, this->indexOffset);
//     }
//     else
//     {
//         glBindBuffer(GL_ARRAY_BUFFER, this->vboBuffer);
//         glDrawArrays(this->renderMode, 0, this->indexCount);
//     }
// }