#pragma once

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    auto bind() -> void;

private:
    unsigned int m_id;
};
