#version 330

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

in vec3 position;

out vec3 fColor;
out vec3 fTexCoord;

void main() {
    // Computes vertex position in the screen space
    gl_Position = projection * view * model * vec4(position, 1.0);
    fColor = vec3(1.0, 1.0, 1.0);
    fTexCoord = position;
}
