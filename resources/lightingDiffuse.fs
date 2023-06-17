#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

float dist(in vec3 a, in vec3 b) {
    return (b.x-a.x)*(b.x-a.x)+\
    (b.y-a.y)*(b.y-a.y)+\
    (b.z-a.z)*(b.z-a.z);
}

void main() {
    // Ambient
    float ambientStrength = 0.1;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 diffuse = diff * lightColor;
    
    vec3 ambient = ambientStrength * lightColor;


    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;


    FragColor = vec4(result, 1.0);
}
