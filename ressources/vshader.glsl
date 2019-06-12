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
out vec3 fNormalsCoord;
out vec3 fFragPos;

void main() {
    // Computes the vertex position in screen space
    gl_Position = projection * view * model * vec4(position, 1.0);

    // Passes the color to the fragment shader
    fColor = color;
    // Pases the texture coordinates to the fragment shader
    fTexCoord = texCoord;
    // Pases the normal coordinates to the fragment shader
    fNormalsCoord = mat3(transpose(inverse(model))) * normalsCoord;
    // Pases the fragment position coordinates to the fragment shader
    fFragPos = vec3(model * vec4(position, 1.0));
}
