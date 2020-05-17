#version 330 core
layout(location = 0) in vec3 in_Position;
layout(location = 2) in vec3 in_Normal;
//layout(location = 1) in vec3 in_Color;

// model, view and projection separately
uniform mat4 modelview;
uniform mat4 projection;
uniform vec4 lightPos;  

out vec3 ex_Normal;
out vec3 FragPos;
out vec3 lightVector; 

void main(void)
{
    FragPos = (modelview * vec4(in_Position,1.0)).xyz;

    lightVector = normalize(lightPos.xyz - FragPos);
    
	// Multiply the mvp matrix by the vertex to obtain our final vertex position
	// gl_Position is an output variable defined by standards
    ex_Normal = normalize((modelview*vec4(in_Normal,0.0)).xyz);
	gl_Position = projection * modelview * vec4(in_Position,1.0);
}
