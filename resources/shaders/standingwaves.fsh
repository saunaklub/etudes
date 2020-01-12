#version 330 core

#define PI 3.141592653589793

uniform vec2 resolution = vec2(1920, 1080);
uniform float time = 0;

uniform float in1 = 0;
uniform float in2 = 0;
uniform float in3 = 0;
uniform float in4 = 0;
uniform float env = 0;

float c  = 0;
out vec4 color;

void main() {
    // float aspect_x = max(1.0, resolution.x / resolution.y);
    // float aspect_y = max(1.0, resolution.y / resolution.x);

    vec2 p = gl_FragCoord.xy / resolution;
        //- vec2(aspect_x, aspect_y);

    // 2D standing wave equation
    float kx = 10 * in1 * PI;
    float ky = 10 * in2 * PI;

    float sinx = sin(kx * p.x);
    float siny = sin(ky * p.y);
    float cost = cos(in4*5*time + p.x*p.y*in2*5);
    float z = sinx*sinx*siny*siny*cost;

    z = (z + 1)/2;

    // float r = env *(p.x+p.y) *0.5 * in3;
    // float g = sin(p.y * time / 10)  * in1 -p.;
    // float b = sin(p.x + sin(time*10) / 10) * in2;

    // float r = z;
    // float g = clamp(1-z, 0.4, 0.9);
    // float b = env * in3;//clamp((z), 0.2, 0.8);

    float r = z;
    float g = clamp(1-z, 0.4, 0.5);
    float b = env * in3;//clamp((z), 0.2, 0.8);

    color = vec4(r, g, b, 1);
  }
