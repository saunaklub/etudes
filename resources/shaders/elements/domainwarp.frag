// (c) KukaTails, retreived from shadertoy.com

#version 330 core

uniform ivec2 resolution;

uniform float lacunarity = 2.0;
uniform float H = 0.26;

out vec4 fragColor;

float Hash(vec2 p)
{
    float h = dot(p, vec2(17.1, 311.7));
    return -1.0 + 2.0 * fract(sin(h) * 4358.5453);
}

float Noise(vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);
    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(mix(Hash(i + vec2(0.0, 0.0)),
                   Hash(i + vec2(1.0, 0.0)), u.x),
               mix(Hash(i + vec2(0.0, 1.0)),
                   Hash(i + vec2(1.0, 1.0)), u.x), u.y);
}

float FbmNoise(vec2 p)
{
  const float octaves = 3.5;

  float value = 0.0, k = 0.0;
  for (float i = 0.0; i < octaves; ++i) {
    value += Noise(p) * pow(lacunarity, -H * i);
    p *= lacunarity;
    ++k;
  }

  float remainder = fract(octaves);
  if (remainder != 0.0) {
    value += remainder * Noise(p) * pow(lacunarity, -H * k);
  }

  return value;
}

float Pattern(vec2 p)
{
    vec2 q = vec2(FbmNoise(p + vec2(0.0, 0.0)),
                  FbmNoise(p + vec2(-0.3, 0.6)));
    vec2 r = vec2(FbmNoise(p + 0.4 * q + vec2(0.1, 0.5)),
                  FbmNoise(p + 0.5 * q + vec2(0.8, 0.3)));
    return FbmNoise(r);
}

vec3 GetColor(vec2 p)
{
    float pattern_value = Pattern(3.0 * p);
    vec3 col = mix(vec3(0.2,0.1,0.4), vec3(0.3,0.05,0.05), pattern_value);
    col = mix(col, vec3(0.9,0.9,0.9), 2.0 * pattern_value * pattern_value);
    col = mix(col, vec3(0.2,0.1,0.4), 0.2 * pattern_value * pattern_value * pattern_value);
    col = clamp( col*pattern_value*2.0, 0.0, 1.0 );
    return col;
}

void main()
{
  vec2 p = gl_FragCoord.xy / resolution.xy;
  vec2 uv = p * vec2(resolution.x / resolution.y, 1.0);
  vec3 color = GetColor(uv);

  fragColor = vec4(color, 1.0);
}
