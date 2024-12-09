#include "VertexArray.hpp"
#include "glad/glad.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

auto VertexArray::bind() -> void
{
    glBindVertexArray(m_id);
}
