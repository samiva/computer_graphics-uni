#version 430 core

// in vec3 ex_color;
in vec3 ex_texcoord;

uniform samplerCube _skyboxtex;

out vec4 fcolor;

void main() {
    fcolor = /* vec4(1.0f,1.0f,0.0f,1.0f); */ texture(_skyboxtex, ex_texcoord);
}