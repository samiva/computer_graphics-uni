#version 430 core
layout (location=0) out vec4 fragColor;
in vec2 ex_texcoord;

uniform sampler2D texture0;

void main(void) {
    vec3 texColor = texture2D(texture0, ex_texcoord).rgb;
    fragColor = vec4(1.0f-texColor.r, 1.0f-texColor.g,1.0f-texColor.b,1.0f);
}