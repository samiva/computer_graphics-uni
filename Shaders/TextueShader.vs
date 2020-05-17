#version 430 core
layout (location=0) in vec3 in_position;
layout (location=2) in vec3 in_normal;
layout (location=3) in vec2 in_texcoord;

out vec2 ex_texcoord;

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _proj;

void main(void) {
    float scaleFactor = 1.0f;
    mat4 mvp = _proj*_view*_model;
    ex_texcoord = in_texcoord;
    
    gl_Position = mvp*vec4(in_position*scaleFactor, 1.0f);    
}