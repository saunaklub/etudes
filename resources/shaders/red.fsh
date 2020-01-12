#version 330 core

uniform vec2 resolution = vec2(1920, 1080);
uniform float time = 0;

uniform float in1 = 0;
uniform float in2 = 0;
uniform float in3 = 0;
uniform float in4 = 0;

out vec4 color;

void main() {
    // float aspect_x = max(1.0, resolution.x / resolution.y);
    // float aspect_y = max(1.0, resolution.y / resolution.x);

    vec2 p = gl_FragCoord.xy / resolution;
        //- vec2(aspect_x, aspect_y);

    float r = p.x * in1 + p.y * in2;
    float g = p.y * in3;//cos(time) * cos(time);
    float b = 1 - p.x*in4 + p.y;//r + g;

    color = vec4(r, g, b, 1);
}
