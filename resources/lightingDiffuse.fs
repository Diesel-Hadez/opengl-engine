#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

in vec3 Normal;
in vec3 FragPos;

float dist(in vec3 a, in vec3 b) {
    return (b.x-a.x)*(b.x-a.x)+\
    (b.y-a.y)*(b.y-a.y)+\
    (b.z-a.z)*(b.z-a.z);
}

void main() {
    float ambientStrength = 0.1;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 diffuse = diff * lightColor;
    
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
