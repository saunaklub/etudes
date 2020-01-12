#version 330 core

in vec3 vertPos;
in vec2 vertUV;

out vec2 uv;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(vertPos, 1);
    uv = vertUV;
}
