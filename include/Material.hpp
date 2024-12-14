#pragma once

#include "Shader.hpp"

class Material
{
public:
    Material(const Shader& shader);
    auto bind() const -> void;

private:
    const Shader* m_shader;
};
