#version 330

uniform sampler2D modelTexture;

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

    fragColor = vec4(ambient + diffuse, 1.0f) * texture(modelTexture, fTexCoord);
}
