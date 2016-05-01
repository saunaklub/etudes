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

    float x;
    float y;
    float sinusoid;
    float dist;

    switch(mode) {
    case 0:
        x = uv.x;
        y = uv.y;

        sinusoid =
            (sin(2.f*PI * ((order*(x * lambda + freq * time)) + phase))
             * (1-stroke_width) + 1.f) / 2.f;

        dist = abs(y - sinusoid);

        // shade along line length
        shaded.a *= sin(PI*uv.x);
        break;
    case 1:
        // x == phi
        // y == r
        x = atan(0.5f - uv.y, 0.5f - uv.x) / PI + 1.0f;
        y = length(2.0f * vec2(0.5f - uv.x, 0.5f - uv.y));

        float circular_amp_length = 1 - 0.9f / order;
        y = clamp((y - circular_amp_length) /
                  (1 - circular_amp_length) * 2.0f - 1.0f,
                  -1, 1);
        sinusoid =
            (sin(2.f*PI * (order * (x + lambda * time) + phase))
             * (1-stroke_width) + 1.f) / 2.f;

        sinusoid *= (sin(2.f * PI * freq * order * time));

        dist = y - sinusoid;
        dist = abs(dist);

        break;
    }


    // shade with distance from sinusoid and blur factor
    float blur_start_dist = stroke_width / 2.0f * (1.0f - stroke_blur);
    float blur_width = stroke_width / 2.f - blur_start_dist;
    if(dist > blur_start_dist)
        shaded.a *=  1.0f - (dist-blur_start_dist) / blur_width;

    shaded = clamp(shaded, 0, 1);

    out_color = shaded;
}
