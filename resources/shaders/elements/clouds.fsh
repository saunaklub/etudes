#version 330 core

in vec2 uv;

out vec4 outColor;

struct NoiseLayer
{
    float freq;
    float amplitude;
    vec2 origin;
    vec4 color;
};

uniform float scale;

const int numLayers = 3;
uniform NoiseLayer layers[numLayers];

const vec4 pParam = vec4( 17.0*17.0, 34.0, 1.0, 7.0);


vec2 permute(vec2 x0, vec3 p) {
    vec2 x1 = mod(x0 * p.y, p.x);
    return floor(  mod( (x1 + p.z) *x0, p.x ));
}

vec3 permute(vec3 x0,vec3 p) {
  vec3 x1 = mod(x0 * p.y, p.x);
  return floor(  mod( (x1 + p.z) *x0, p.x ));
}

float taylorInvSqrt(float r)
{
    return ( 0.83666002653408 + 0.7*0.85373472095314 - 0.85373472095314 * r );
}

float simplexNoise2(vec2 v)
{
    const vec2 C = vec2(0.211324865405187134, // (3.0-sqrt(3.0))/6.;
                        0.366025403784438597); // 0.5*(sqrt(3.0)-1.);
    const vec3 D = vec3( 0., 0.5, 2.0) * 3.14159265358979312;
// First corner
    vec2 i  = floor(v + dot(v, C.yy) );
    vec2 x0 = v -   i + dot(i, C.xx);

// Other corners
    vec2 i1  =  (x0.x > x0.y) ? vec2(1.,0.) : vec2(0.,1.) ;

    //  x0 = x0 - 0. + 0. * C
    vec2 x1 = x0 - i1 + 1. * C.xx ;
    vec2 x2 = x0 - 1. + 2. * C.xx ;

// Permutations
    i = mod(i, pParam.x);
    vec3 p = permute(permute(
                         i.y + vec3(0., i1.y, 1. ), pParam.xyz)
                     + i.x + vec3(0., i1.x, 1. ), pParam.xyz);

// ( N points uniformly over a line, mapped onto a diamond.)
    vec3 x = fract(p / pParam.w) ;
    vec3 h = 0.5 - abs(x) ;

    vec3 sx = vec3(lessThan(x,D.xxx)) *2. -1.;
    vec3 sh = vec3(lessThan(h,D.xxx));

    vec3 a0 = x + sx*sh;
    vec2 p0 = vec2(a0.x,h.x);
    vec2 p1 = vec2(a0.y,h.y);
    vec2 p2 = vec2(a0.z,h.z);

    p0 *= taylorInvSqrt(dot(p0,p0));
    p1 *= taylorInvSqrt(dot(p1,p1));
    p2 *= taylorInvSqrt(dot(p2,p2));

    vec3 g = 2.0 * vec3( dot(p0, x0), dot(p1, x1), dot(p2, x2) );

// mix
    vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x1,x1), dot(x2,x2)), 0.);
    m = m*m ;
    return 1.66666* 70.*dot(m*m, g);
}

void main() {
    vec2 offsetNoise = uv - 0.5;
    vec4 color = vec4(0, 0, 0, 0);

    for(int layer = 0 ; layer < numLayers ; ++layer) {
        color += layers[layer].color * layers[layer].amplitude *
            (simplexNoise2(layers[layer].origin +
                          layers[layer].freq*scale*offsetNoise) + 1.0) * 0.5;
    }

    outColor = color;
}
