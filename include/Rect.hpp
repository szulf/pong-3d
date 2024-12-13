#pragma once

#include "Mesh.hpp"
#include <vector>

class Rect
{
public:
    Rect(const std::vector<float>& vertex_data);
    auto render() -> void;

private:
    Mesh* mesh;
};
