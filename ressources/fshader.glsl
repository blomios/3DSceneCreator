#version 330

uniform sampler2D modelTexture;
uniform vec3 viewPos;
uniform vec3 lightPos;

in vec3 fColor;
in vec2 fTexCoord;
in vec3 fNormalsCoord;
in vec3 fFragPos;

out vec4 fragColor;

void main() {
    // The position of the Sun
    //vec3 lightPos = vec3(1.2f, 1.2f, 1.2f);
    // Color of the light source (the Sun here) : white
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    // Normalizes the normal vector of the fragment
    vec3 norm = normalize(fNormalsCoord);
    // Normalizes the light direction, which is a vector between the light position and the fragment position
    vec3 lightDir = normalize(lightPos - fFragPos);


    // AMBIENT
    float ambientStrength = 1.0;
    vec3 ambient = ambientStrength * lightColor;

    // DIFFUSE : Brightness where the fragments are aligned to the light rays
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // SPECULAR : Strong brightness where the camera is looking
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Final frag color : ambient + diffuse + specular + texture
    fragColor = vec4(ambient + diffuse + specular, 1.0f) * texture(modelTexture, fTexCoord);
}
