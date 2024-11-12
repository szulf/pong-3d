#pragma once

#include <string>
class Shader {
public:
    Shader(const std::string& vert_file, const std::string& frag_file);
    ~Shader();

    void bind();
private:
    int m_id;
};
