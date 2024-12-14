#include "Renderer.hpp"

template <typename T>
    requires is_renderable<T>
auto submit(const T& renderable) -> void
{

}
