#version 330 core

in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1);
}
