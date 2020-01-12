#version 330 core

#define PI 3.141592653589793
#define MAX_MARCHING_STEPS 100
#define EPSILON 0.000001

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

out vec4 color;

float timeFract = fract(time/5);
float timeFractS = fract(time/10);

float intersect(float sdf1, float sdf2) {
    return max(sdf1, sdf2);
}

float join(float sdf1, float sdf2) {
    return min(sdf1, sdf2);
}

float subtract(float sdf1, float sdf2) {
    return intersect(sdf1, -sdf2);
}

float sphereSDF(vec3 p, vec3 center, float r) {
    return length(p-center) - r;
}

float sphereSDF(vec3 p) {
    return sphereSDF(p, vec3(0,0,0), 1);
}

float boxSDF(vec3 p, vec3 b, vec3 center) {
    return length(max(abs(p-center)-b, 0.0));
}

float sceneSDF(vec3 p) {
    return subtract(boxSDF(p, vec3(0.3, 0.1, 0.3), vec3(0, -0.2, 0)),
                    sphereSDF(p, vec3(0,0,0), timeFract*0.5));
}

float start = 0.0;
float end = 100.0;
vec2 marchDepth(vec3 eye, vec3 rayDirection) {
    float depth = start;

    for (int i = 0; i < MAX_MARCHING_STEPS; i++)
    {
        float dist = sceneSDF(eye + depth * rayDirection);

        if (dist < EPSILON) {
            return vec2(depth, float(i)/MAX_MARCHING_STEPS);
        }

        depth += dist * 0.7;

        if (depth >= end) {
            return vec2(end, float(i)/MAX_MARCHING_STEPS);
        }
    }

    return vec2(end, 1);
}

vec3 estimateNormal(vec3 p) {
    return normalize(vec3(
        sceneSDF(vec3(p.x + EPSILON, p.y, p.z)) -
        sceneSDF(vec3(p.x - EPSILON, p.y, p.z)),
        sceneSDF(vec3(p.x, p.y + EPSILON, p.z)) -
        sceneSDF(vec3(p.x, p.y - EPSILON, p.z)),
        sceneSDF(vec3(p.x, p.y, p.z  + EPSILON)) -
        sceneSDF(vec3(p.x, p.y, p.z - EPSILON))
    ));
}

mat4 viewMatrix(vec3 eye, vec3 center, vec3 up) {
    vec3 f = normalize(center - eye);
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);
    return mat4(
        vec4(s, 0.0),
        vec4(u, 0.0),
        vec4(-f, 0.0),
        vec4(0.0, 0.0, 0.0, 1)
        );
}

void main() {
    // float aspect_x = max(1.0, resolution.x / resolution.y);
    // float aspect_y = max(1.0, resolution.y / resolution.x);

    vec2 fragCoord = gl_FragCoord.xy;
    // float ampTwist = 0.05;
    // fragCoord.x += sin(fragCoord.y * in6 * ampTwist) * 100 * in7;
    // fragCoord.y += sin(fragCoord.x * in6 * ampTwist) * 100 * in7;

    // vec2 scaleViewport = vec2(0.55, 0.5);
    // fragCoord = fragCoord / scaleViewport + (1 - scaleViewport);

    vec2 fragPos = fragCoord / resolution;

    vec3 eye = vec3(0, 0, 0.1 + in1);

    vec3 imageCenter = vec3(0, 0, 0);
    vec3 imageUp = vec3(0, 1, 0);
    vec3 imageRight = vec3(1, 0, 0);
    vec2 imageExtends = vec2(16/9.0, 1);

    vec3 imagePoint = imageCenter +
        (fragPos.x-0.5) * imageExtends.x * imageRight +
        (fragPos.y-0.5) * imageExtends.y * imageUp;

    vec3 viewDirection = normalize(imagePoint - eye);

    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 1;

    vec2 result = marchDepth(eye, viewDirection);

    if(result.x != end) {
//        color.rgb = estimateNormal(eye + result.x * viewDirection) * result.y;
        color.rgb = estimateNormal(eye + result.x * viewDirection);
    }
    else {
        color.g = result.y;
    }

//    color.xyz = color.xyz - 2 * invert * color.xyz + vec3(1,1,1)*invert;
}
