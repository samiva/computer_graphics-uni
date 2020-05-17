#version 330 core
in vec3 ex_Normal;
in vec3 FragPos;
in vec3 lightVector; // L
layout (location = 0) out vec4 fragColor;

uniform vec3 lightcolor;
uniform vec4 lightposition;
uniform vec4 viewpos;

uniform vec3 color;
uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float mShininess;

void main(void) {
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

    float lightDst = length(lightVector);
    float lightAttenuation = 1/lightDst;

    vec3 res = lightAttenuation * vec3(ambientProduct + diffuse + specular) * color;
    fragColor = vec4(res,1.0);
}
 