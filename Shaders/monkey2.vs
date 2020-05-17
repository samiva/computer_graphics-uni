#version 330 core
layout(location = 0) in vec3 in_Position;
layout(location = 2) in vec3 in_Normal;

out vec4 ex_fragColor;
//layout(location = 1) in vec3 in_Color;

vec3 ex_Normal;
vec3 FragPos;
vec3 lightVector; // L

// model, view and projection separately
uniform mat4 modelview;
uniform mat4 projection;
uniform vec4 lightPos;

uniform vec3 lightcolor;
uniform vec4 lightposition;
uniform vec4 viewpos;

uniform vec3 color;
uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float mShininess;

void main(void)
{
    FragPos = (modelview * vec4(in_Position,1.0)).xyz;

    lightVector = normalize(lightPos.xyz - FragPos);
    
	// Multiply the mvp matrix by the vertex to obtain our final vertex position
	// gl_Position is an output variable defined by standards
    ex_Normal = normalize((modelview*vec4(in_Normal,0.0)).xyz);

     vec3 norm = normalize(ex_Normal); // N

    float diffuseCoef = max(dot(lightVector, norm), 0.0f);
    vec4 diffuse = diffuseCoef*diffuseProduct;

    // Calculate specular
    vec3 viewDir = normalize(-FragPos); // normalize(viewpos.xyz - FragPos); // E
    vec3 half = normalize(lightVector.xyz+viewDir); //reflect(-lightVector.xyz, norm); // H
    float spec = pow(max(dot(norm, half),0.0), mShininess);
    vec4 specular = spec * specularProduct;
    
    if(dot(lightVector.xyz,norm) < 0.0) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    vec3 res = vec3(ambientProduct + diffuse + specular) * color;
    ex_fragColor = vec4(res, 1.0);
	gl_Position = projection * modelview * vec4(in_Position,1.0);
}
