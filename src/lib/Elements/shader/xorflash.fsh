#version 330 core

#define PI 3.141592653589793

uniform vec2 resolution = vec2(1920, 1080);
uniform float time = 0;

uniform float in1 = 0;
uniform float in2 = 0;
uniform float in3 = 0;
uniform float in4 = 0;
uniform float env = 0;
uniform float brightness = 0;

float c  = 0;
out vec4 color;

void main() {
    // float aspect_x = max(1.0, resolution.x / resolution.y);
    // float aspect_y = max(1.0, resolution.y / resolution.x);

    vec2 p = gl_FragCoord.xy / resolution;
        //- vec2(aspect_x, aspect_y);

    int i1 = int(gl_FragCoord.x*7 + time*400);
    int i2 = int(gl_FragCoord.y*7 + time*300) ^ int(time*100)  ;
    int i = (i2) ^ (i1);

    int stride = 0x1000;
    float f = float(i%stride) / float(stride);

    float r = f * in3;
    float g = in1 * brightness;
    float b = in2 * brightness;

    color = vec4(r, g, b, 1);
  }
