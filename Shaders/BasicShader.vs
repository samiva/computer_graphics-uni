#version 430 core
layout (location=0) in vec3 in_position;

uniform mat4 _viewMat;
uniform mat4 _projMat;
uniform mat4 _modelMat;

void main(void) {
    mat4 mvp = _projMat * _viewMat * _modelMat;
    gl_Position = mvp * vec4(in_position, 1.0f);
}