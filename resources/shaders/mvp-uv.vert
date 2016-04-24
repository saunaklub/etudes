#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertUV;

out vec2 uv;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(vertPos, 1);
    uv = vertUV;
}
