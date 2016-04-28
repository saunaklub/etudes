#version 330 core

in vec2 uv;
out vec4 out_color;

uniform vec4 color;
uniform float width;

uniform int order;
uniform float time;
uniform float phase;
uniform float freq;
uniform float lambda;

const float PI = 3.14159265359;

void main() {
    vec4 shaded = color;
    shaded = clamp(shaded, 0, 1);

    // shade with distance from sinusoid
    float sinusoid =
        (sin(2.f*PI * ((order*(uv.x * lambda + freq * time)) + phase)) *
         (1-width) + 1.f) / 2.f;

    float dist = abs(uv.y - sinusoid);
    shaded *=  -dist / width / 2.0f + 1;

    // shade along line length
    shaded *= sin(PI*uv.x);

    out_color = shaded;
}
