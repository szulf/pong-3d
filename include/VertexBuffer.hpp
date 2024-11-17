#pragma once

#include <vector>

class VertexBuffer {
public:
    VertexBuffer(const std::vector<float>& data, unsigned int vertex_stride);
    ~VertexBuffer();

    inline void bind();

    template <typename T>
    void set_attrib_pointer(unsigned int size, unsigned int pointer);

private:
    unsigned int m_id;
    unsigned int m_vertex_stride;
    unsigned int m_pos;
};
