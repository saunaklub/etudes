#version 330 core

#define PI 3.141592653589793

uniform vec2 resolution = vec2(1920, 1080);
uniform float time = 0;

uniform float in1 = 0;
uniform float in2 = 0;
uniform float in3 = 0;
uniform float in4 = 0;
uniform float in5 = 0;
uniform float in6 = 0;
uniform float in7 = 0;
uniform float in8 = 0;
uniform float env = 0;
uniform float brightness = 0;
uniform float invert = 0;

bool drop = false;

vec4 color1 = vec4(0.0, in8, in8, 1);
vec4 color2 = vec4(1, 1, 1, 1);
vec4 color3 = vec4(0, 0.8, 1, 1);

float c  = 0;
out vec4 color;

float relWeight(float val, float sensitivity) {
    return (1-sensitivity) + val * sensitivity;
}

void main() {
    // float aspect_x = max(1.0, resolution.x / resolution.y);
    // float aspect_y = max(1.0, resolution.y / resolution.x);

    vec2 fragCoord = gl_FragCoord.xy;
    float ampTwist = 0.05;
    fragCoord.x += sin(fragCoord.y * in6 * ampTwist) * 100 * in7;
    fragCoord.y += sin(fragCoord.x * in6 * ampTwist) * 100 * in7;

    vec2 scaleViewport = vec2(0.55, 0.5);
    fragCoord = fragCoord / scaleViewport + (1 - scaleViewport);

    vec2 p = fragCoord / resolution;
        //- vec2(aspect_x, aspect_y);

//    color3.g = p.x * 4 + mod(time, 1);
    color2.r = p.y;
//    color3.b = 1-p.x;

    //float d = length(float(gl_FragCoord.xy - (int(gl_FragCoord.xy) & ~0xF))) / 0xF;

    float timeFrac = mod(time/10, 1);
    float sinPosF = (sin(time/50) / 2) + 1.0;
    float sinPosS = (sin(time/20) / 2) + 1.0;

    int rand = (int(fragCoord.x/in2/20 - time*1) ^
                int(fragCoord.y/in2/18 + time*3));

    int moduloMax = 24;

    int offsetAmp = 4;
    int offset = int(clamp(mod(time/4/offsetAmp, 1) * offsetAmp, 0, moduloMax - offsetAmp));

    bool cond1 = rand % int(in4*moduloMax) == 0;
    bool cond2 = rand % int(in3*moduloMax+ offset) == 0;
    if(( cond1 || cond2))
    {
        if(cond1) {
            // color.r = brightness;
            // color.g = brightness * in1;
            // color.b = brightness;//d * brightness * in1 * 2;
            color = color1 * relWeight(env, 0.4);
//            discard;
        }
        if(cond2) {
            color = color2 * relWeight(env, 1.0);
//            discard;
        }
        if(cond1 && cond2) {
            color = color3 * relWeight(brightness, 0.6);
        }
    }
    else {
        if(rand % int(20*in1) == 0) {
            color.r = relWeight(brightness, 1.0);
            color.g = mod(gl_FragCoord.x/resolution.x, 1) * relWeight(brightness, 0.8);
            color.b = 0;
            color.a = 1;
        }
        else {
            drop = true;
        }

        // color.r = 0;
        // color.g = 0;
        // color.b = 0;

//        discard;
    }

    if(drop) {
        discard;
        color.r = 0;
        color.g = 0;
        color.b = 0;
        color.a = 0.02;
    }
    else {
        color.xyz = color.xyz - 2 * invert * color.xyz + vec3(1,1,1)*invert;
    }


    // color.r = float(rand % int(58*pow(sinPosF, 0.2))) / 60 * (env) * (1-p.x);
    // color.g = float(rand % int(100*pow(sinPosS, 3))) / 100 * env;
    // color.b = p.y;
    // color.a = 1.0;
  }
