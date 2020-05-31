#version 330 core
in vec3 ex_Normal;
in vec3 FragPos;
in vec3 lightVector; // L
layout (location = 0) out vec4 fragColor;

uniform vec3 _lightcolor;
uniform vec4 _lightPos;
uniform vec4 _viewpos;

uniform vec3 _objectColor;
uniform vec4 _ambientProduct;
uniform vec4 _diffuseProduct;
uniform vec4 _specularProduct;
uniform float _mShininess;

void main(void) {
    vec3 norm = normalize(ex_Normal); // N

    float diffuseCoef = max(dot(lightVector, norm), 0.0f);
    vec4 diffuse = diffuseCoef*_diffuseProduct;

    // Calculate specular
    vec3 viewDir = normalize(_viewpos.xyz-FragPos); // normalize(_viewpos.xyz - FragPos); // E
    vec3 halfVec = lightVector.xyz+viewDir; //reflect(-lightVector.xyz, norm); // H
    float spec = pow(max(dot(norm, halfVec),0.0), _mShininess);
    vec4 specular = spec * _specularProduct;
    
    if(dot(lightVector.xyz,norm) < 0.0) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    float lightDst = length(vec3(_lightPos)-FragPos);
    float lightAttenuation = 1/lightDst;

    vec3 res = lightAttenuation * vec3(_ambientProduct + diffuse + specular) * _objectColor;
    fragColor = vec4(res,1.0);
}
 