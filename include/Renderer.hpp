#pragma once

#include <concepts>
#include <vector>

template <typename T>
concept is_renderable = requires(T t)
{
    { t.render() } -> std::same_as<void>;
};

class Renderer
{
public:
    template <typename T>
        requires is_renderable<T>
    auto render(const std::vector<T>& render_list) -> void;

    template <typename T>
        requires is_renderable<T>
    auto render(const T& render_item) -> void;

    template <typename T>
        requires is_renderable<T>
    auto submit(const T& renderable) -> void;

private:
};
