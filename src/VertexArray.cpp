#include "VertexArray.hpp"
#include "glad/glad.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() {
    glBindVertexArray(m_id);
}
