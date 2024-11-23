#include "VertexBuffer.hpp"
#include "Window.hpp"
#include <cstdio>

VertexBuffer::VertexBuffer(const std::vector<float>& data, unsigned int vertex_stride) : m_vertex_stride{vertex_stride}, m_pos{0}
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

template <>
void VertexBuffer::set_attrib_pointer<float>(unsigned int size, unsigned int pointer)
{
    glVertexAttribPointer(m_pos, size, GL_FLOAT, false, m_vertex_stride * sizeof(float), reinterpret_cast<void*>(pointer * sizeof(float)));
    glEnableVertexAttribArray(m_pos);

    m_pos++;
}
