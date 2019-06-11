#version 330

uniform sampler2D modelTexture;
uniform vec3 viewPos;

in vec3 fColor;
in vec2 fTexCoord;
in vec3 fnormalsCoord;
in vec3 FragPos;

out vec4 fragColor;

void main() {

    vec3 lightPos = vec3(1.2,1.2,1.2);

    vec3 norm = normalize(fnormalsCoord);
    vec3 lightDir = normalize(lightPos - FragPos);


    vec3 lightColor = vec3(1.0f,1.0f,1.0f);

    float ambientStrength = 1.0;
    vec3 ambient = ambientStrength * lightColor;


    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    fragColor = vec4(ambient + diffuse + specular, 1.0f) * texture(modelTexture, fTexCoord);
}
