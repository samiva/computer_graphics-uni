#version 430 core

layout (location = 0) in vec3 in_pos;
// layout (location = 1) in vec3 in_color;

uniform mat4 _mvp; 

out vec3 ex_color;
out vec3 ex_texcoord;

void main() {
    gl_Position = vec4(_mvp*vec4(in_pos, 1)).xyww;
    // ex_color = in_color;
    ex_texcoord = in_pos;
}