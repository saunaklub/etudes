#version 330 core

in vec2 uv;
out vec4 out_color;

uniform vec4 color;
uniform int order;

uniform float time;
uniform float phase;
uniform float f0;

const float PI = 3.14159265359;
const float width = 0.3;

const float freq = .3f;

const float f0min = 80;
const float f0max = 600;

void main() {
    float f0norm = (f0 - f0min) / (f0max - f0min);

    vec4 shaded = color;
    shaded = clamp(shaded, 0, 1);

    // shade with distance from sinusoid
    float sinusoid =
        (sin(2.f*PI * ((order*(uv.x + freq * time)) + phase)) *
         (1-2*width) + 1.f) / 2.f;

    float dist = abs(uv.y - sinusoid);
    shaded *=  -dist / width + 1;
    // if(dist > width)
    //     shaded = vec4(1, 0, 0, 0);

    // shade along line length
    shaded *= sin(PI*uv.x);

    out_color = shaded;
}
