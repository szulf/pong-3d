#pragma once

struct VertexAttrib
{
    unsigned int size;
    unsigned int type;
    bool normalized;
    int stride;
    void* offset;
};
