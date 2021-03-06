#version 330 core

in vec2 uv;
out vec4 color;

uniform sampler2D texSampler;

uniform float shiftHue = 0.0f;
uniform float shiftSaturation = 0.0f;
uniform float shiftValue = 0.0f;

uniform float alpha = 1.0f;
uniform bool useAlpha = true;

vec3 rgb2hsv(vec3 c) {
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main(){
    vec4 color4 = texture(texSampler, uv);
    vec3 c = color4.xyz;

    c = rgb2hsv(c);
    c.x += shiftHue;
    c.x = mod(c.x, 1);
    // c.y += shiftSaturation;
    // c.y = mod(c.y, 1);
    // c.z += shiftValue;
    // c.z = mod(c.z, 1);
    c = hsv2rgb(c);

    color = vec4(c, color4.a * alpha);

    if(!useAlpha)
        color.a = 1.0f;
}
