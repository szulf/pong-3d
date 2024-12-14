#include "Rect.hpp"

Rect::Rect(const Mesh &mesh, const Material &material, const glm::mat4 &model) {
  m_mesh = &mesh;
  m_material = &material;
  m_model = model;
}

auto Rect::prepare(Renderer& renderer) -> void
{
    renderer.submit(*this);
}
