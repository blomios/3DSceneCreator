#version 330

uniform sampler2D testTexture;

in vec3 fColor;
in vec2 fTexCoord;

out vec4 fragColor;

void main() {
    //fragColor = vec4(fColor, 1.0);
    fragColor = texture(testTexture, fTexCoord);
}
