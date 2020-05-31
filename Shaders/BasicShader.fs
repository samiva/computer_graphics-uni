#version 430 core
out vec4 ex_color;

uniform vec3 _objectColor;

void main(void) {
    ex_color = vec4(_objectColor,1.0f);
}