#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in float a_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out float color;

void main() {
    gl_Position = projection * view * model * vec4(a_pos, 1.0f);
    color = a_color;
}
