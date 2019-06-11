#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 position;
in vec3 color;
in vec2 texCoord;
in vec3 normalsCoord;

out vec3 fColor;
out vec2 fTexCoord;
out vec3 fnormalsCoord;
out vec3 FragPos;

void main() {
    // Calculate vertex position in screen space
    gl_Position = projection * view * model * vec4(position, 1.0);
    fColor = color;
    fTexCoord = texCoord;
    fnormalsCoord = normalsCoord;
    FragPos = vec3(model * vec4(position, 1.0));
}
