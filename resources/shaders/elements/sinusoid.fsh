#version 330 core

in vec2 uv;
out vec4 out_color;

uniform int mode;
uniform int order;

uniform float time;
uniform float freq;
uniform float phase;
uniform float lambda;
uniform float phaseCircular;

uniform float circleWidth;
uniform float strokeWidth;
uniform float strokeBlur;

uniform vec4 color;

const float PI = 3.14159265359;

void main() {
    vec4 shaded = color;
    shaded = clamp(shaded, 0, 1);

    float x;
    float y;
    float sinusoid;
    float dist = 0.f;

    switch(mode) {
    case 0:
        x = uv.x;
        y = uv.y;

        sinusoid =
            (sin(2.f*order*(x * lambda) + phase)
             * (1-strokeWidth) + 1.f) / 2.f;

        dist = abs(y - sinusoid);

        // shade along line length
        shaded.a *= sin(PI*uv.x);
        break;
    case 1:
        // x == phi
        // y == r
        x = atan(0.5f - uv.y, 0.5f - uv.x) + PI;
        y = 2.f*length( vec2(uv.x-0.5f, uv.y-0.5f));

        float circle_amp_length = 1 - circleWidth / order;
        y = clamp((y - circle_amp_length) /
                  (1 - circle_amp_length),
                  -1, 1);
        sinusoid =
            (sin( (2.f*order) * x + phaseCircular)) * 0.5f
             * (1-strokeWidth);

        sinusoid *= cos(order * phase);

        dist = y - sinusoid;
        dist = abs(dist);

        break;
    }


    // shade with distance from sinusoid and blur factor
    float blurStartDist = strokeWidth / 2.0f * (1.0f - strokeBlur);
    float blurWidth = strokeWidth / 2.f - blurStartDist;
    if(dist > blurStartDist)
        shaded.a *=  1.0f - (dist-blurStartDist) / blurWidth;

    shaded = clamp(shaded, 0, 1);

    out_color = shaded;
}
