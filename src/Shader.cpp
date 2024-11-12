#include "Shader.hpp"
#include "glad/glad.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string& vert_file, const std::string& frag_file) {
    std::ifstream vert_fstream{vert_file};
    std::stringstream vert_sstream;
    vert_sstream << vert_fstream.rdbuf();
    std::string vert_src = vert_sstream.str();
    const char* vert_src_cstr = vert_src.c_str();

    std::ifstream frag_fstream{frag_file};
    std::stringstream frag_sstream;
    frag_sstream << frag_fstream.rdbuf();
    std::string frag_src = frag_sstream.str();
    const char* frag_src_cstr = frag_src.c_str();

    int status = 0;

    int vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vert_src_cstr, nullptr);
    glCompileShader(vert_shader);

    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::array<char, 512> info_log;
        glGetShaderInfoLog(vert_shader, info_log.size(), nullptr, info_log.data());

        glDeleteShader(vert_shader);
        std::printf("%s\n", info_log.data());
        throw std::runtime_error{"Error compiling vertex shader"};
    }

    int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_src_cstr, nullptr);
    glCompileShader(frag_shader);

    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::array<char, 512> info_log;
        glGetShaderInfoLog(frag_shader, info_log.size(), nullptr, info_log.data());

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);
        std::printf("%s\n", info_log.data());
        throw std::runtime_error{"Error compiling fragment shader"};
    }


    m_id = glCreateProgram();
    glAttachShader(m_id, vert_shader);
    glAttachShader(m_id, frag_shader);
    glLinkProgram(m_id);

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    glGetProgramiv(m_id, GL_LINK_STATUS, &status);
    if (!status) {
        std::array<char, 512> info_log;
        glGetProgramInfoLog(m_id, info_log.size(), nullptr, info_log.data());

        std::printf("%s\n", info_log.data());
        throw std::runtime_error("Error linking shader program");
    }
}

Shader::~Shader() {
    glDeleteProgram(m_id);
}

void Shader::bind() {
    glUseProgram(m_id);
}

template <>
void Shader::set_uniform<float>(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

template <>
void Shader::set_uniform<glm::mat4>(const std::string& name, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
