#pragma once

#include <string>

class Shader
{
public:
    Shader(const std::string& vert_file, const std::string& frag_file);
    ~Shader();

    auto bind() const -> void;

    template <typename T>
    auto set_uniform(const std::string& name, T value) -> void;
private:
    unsigned int m_id;
};
