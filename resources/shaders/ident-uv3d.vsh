#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexUV;

out vec3 UV;

void main() {
    gl_Position = vec4(vertexPosition, 1);
    UV = vertexUV;
}
