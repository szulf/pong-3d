#include "Material.hpp"

Material::Material(const Shader& shader)
{
    m_shader = &shader;
}

auto Material::bind() const -> void
{
    m_shader->bind();
}
