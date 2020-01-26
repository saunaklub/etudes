#version 330 core

in vec3 aPos;
in vec2 aUV;

out vec2 uv;

void main() {
    gl_Position = vec4(aPos, 1);
    uv = aUV;
}
