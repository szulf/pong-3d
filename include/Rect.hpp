#pragma once

#include "Material.hpp"
#include "Mesh.hpp"
#include "Renderer.hpp"
#include "glm/ext/matrix_float4x4.hpp"

class Rect
{
public:
    Rect(const Mesh &mesh, const Material &material, const glm::mat4 &model);

    auto prepare(Renderer& renderer) -> void;

private:
    const Mesh* m_mesh;
    const Material* m_material;
    glm::mat4 m_model;
};
