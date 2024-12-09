#pragma once

#include <span>

class VertexBuffer
{
public:
    VertexBuffer(const std::span<float>& data, unsigned int vertex_stride);
    ~VertexBuffer();

    auto bind() -> void;

    template <typename T>
    auto set_attrib_pointer(unsigned int size, unsigned int pointer) -> void;

private:
    unsigned int m_id;
    unsigned int m_vertex_stride;
    unsigned int m_pos;
};
