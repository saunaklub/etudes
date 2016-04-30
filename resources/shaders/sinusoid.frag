#version 330 core

in vec2 uv;
out vec4 out_color;

uniform int mode;
uniform int order;

uniform float time;
uniform float freq;
uniform float phase;
uniform float lambda;

uniform float stroke_width;
uniform float stroke_blur;

uniform vec4 color;

const float PI = 3.14159265359;

void main() {
    vec4 shaded = color;
    shaded = clamp(shaded, 0, 1);

    float sinusoid =
        (sin(2.f*PI * ((order*(uv.x * lambda + freq * time)) + phase))
         * (1-stroke_width) + 1.f) / 2.f;

    float dist = abs(uv.y - sinusoid);
    float blur_start_dist = stroke_width / 2.0f * (1.0f - stroke_blur);
    float blur_width = stroke_width / 2.f - blur_start_dist;

    // shade with distance from sinusoid and blur factor
    if(dist > blur_start_dist)
        shaded.a *=  1.0f - (dist-blur_start_dist) / blur_width;

    // shade along line length
    shaded.a *= sin(PI*uv.x);

    out_color = shaded;
}
