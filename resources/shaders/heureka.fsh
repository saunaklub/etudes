#version 330 core

uniform vec2 resolution = vec2(800, 600);
uniform float time = 0;

uniform float in1 = 0;
uniform float in2 = 0;
uniform float in3 = 0;
uniform float in4 = 0;

out vec4 color;

void main() {
    float aspect_x = max(1.0, resolution.x / resolution.y);
    float aspect_y = max(1.0, resolution.y / resolution.x);

    vec2 p = 2.0 * gl_FragCoord.xy / min(resolution.x, resolution.y)
        - vec2(aspect_x, aspect_y);

    int i = int(gl_FragCoord.x /4 * (sin(time/10)+2)) ^ int(in1 * (sin(time*1)+1))^ 25;
    i %= 256;
    float fi = i / 255.0;

    float f1 = (sin((p.x+p.y*in1)*6 + time*1)+1.0)/2.0;
    float f2 = (sin(p.y*5+ time)+1.0)/2.0;

    float comb = f1 * f2;
    float single = (sin(p.y * 100 + time))/2.0;

    float r = fi * 0.8;
    float g = single/(f1+f2) - r;
    // float b = single - comb*2;
    float b = r - g;

    if(b < 0.5)
        discard;

    color = vec4(r, g, b, 1);
}
