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

    vec2 fc = gl_FragCoord.xy - resolution/2;
    vec2 p = fc / resolution;
        //- vec2(aspect_x, aspect_y);

    //float d = length(float(gl_FragCoord.xy - (int(gl_FragCoord.xy) & ~0xF))) / 0xF;

//    float d = 1;

    int rand = (int(fc.x/10 * 2 * (sin(time/7)+3)) ^
                int(fc.y/10 * 2 * (sin(time/5)+3))) ^ (int(sin(time*2)*2+8*in2));

//     bool cond1 = rand % int(in4*16) == 0;
//     bool cond2 = rand % int(in3*16 + sin(time/3)) == 0;
//     if(( cond1 || cond2))
//     {
//         if(cond2)
//             color.r = 0.4;//brightness;
//         else
//             color.r = 0;
//         color.g = brightness;
//         color.b = brightness;//d * brightness * in1 * 2;
//     }
//     else {
// //x        discard;
//         color.r = 0.0;
//         color.g = 0;
//         color.b = 0;
// //        discard;
//     }

    float val = float(rand%256) / 255;
    color.r = 1;
    color.g = val;
    color.b = (1-val);


//    color.g = 1-color.g;
//    color = 1 - color;

    // color.a = 0.1 * in1;
   color.a = 1;
  }
