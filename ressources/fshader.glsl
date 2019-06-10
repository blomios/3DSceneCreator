#version 330

uniform sampler2D modelTexture;

in vec3 fColor;
in vec2 fTexCoord;

out vec4 fragColor;

void main() {
    fragColor = texture(modelTexture, fTexCoord);
}
