#version 450 core

in float color;

out vec3 out_color;

void main()
{
    out_color = vec3(color, color, color);
}
