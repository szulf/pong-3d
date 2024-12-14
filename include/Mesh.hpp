#pragma once

#include "VertexAttrib.hpp"
#include <cstddef>
#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices, const std::vector<VertexAttrib> attribs);
    ~Mesh();
    auto bind() const -> void;

private:
    std::size_t m_vertex_count;

    unsigned int m_vao;
    unsigned int m_vbo;
};
