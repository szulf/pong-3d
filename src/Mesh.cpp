#include "Mesh.hpp"
#include "glad/glad.h"

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<VertexAttrib> attribs)
{
    m_vertex_count = vertices.size();

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    for (int i = 0; auto& attrib : attribs)
    {
        glVertexAttribPointer(i, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.offset);
        glEnableVertexAttribArray(i);

        i++;
    }
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

auto Mesh::bind() -> void
{
    glBindVertexArray(m_vao);
}
