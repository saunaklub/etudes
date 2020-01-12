#version 330 core

in vec3 UV;
out vec4 color;

uniform sampler2DArray texSampler;

void main(){
    // vec3 tex = texture(texSampler, UV).rgb;
    // color = vec4(tex.r, tex.g, tex.b, 1.0);
    vec3 tex = texture(texSampler, UV).rgb;
    color = vec4(tex.r, tex.g, tex.b, 1.0);
}
