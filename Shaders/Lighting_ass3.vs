#version 330 core
layout(location = 0) in vec3 in_Position;
layout(location = 2) in vec3 in_Normal;
//layout(location = 1) in vec3 in_Color;

// model, view and projection separately
uniform mat4 _modelview;
uniform mat4 _viewMat;
uniform mat4 _modelMat;
uniform mat4 _projMat;
uniform vec4 _lightPos;  

out vec3 ex_Normal;
out vec3 FragPos;
out vec3 lightVector; 

void main(void)
{
    FragPos = (_modelMat * vec4(in_Position,1.0)).xyz;

    lightVector = normalize(_lightPos.xyz-FragPos);
    
	// Multiply the mvp matrix by the vertex to obtain our final vertex position
	// gl_Position is an output variable defined by standards
    ex_Normal = mat3(inverse(transpose(_modelMat)))*in_Normal;
	gl_Position = _projMat * _viewMat*_modelMat * vec4(in_Position,1.0);
}
