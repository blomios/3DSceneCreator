#version 330

uniform samplerCube skyboxTexture;

in vec3 fColor;
in vec3 fTexCoord;

out vec4 fragColor;

void main() {
    fragColor = texture(skyboxTexture, fTexCoord);
}
