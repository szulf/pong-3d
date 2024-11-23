#pragma once

#include <string>
class Shader
{
public:
    Shader(const std::string& vert_file, const std::string& frag_file);
    ~Shader();

    void bind();

    template <typename T>
    void set_uniform(const std::string& name, T value);
private:
    unsigned int m_id;
};
