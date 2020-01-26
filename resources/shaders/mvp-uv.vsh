#version 330 core

in vec3 aPos;
in vec2 aUV;

out vec2 uv;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(aPos, 1);
    uv = aUV;
}
