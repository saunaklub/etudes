out vec4 outColor;

uniform sampler2DRect uTexture;

void main()
{
    outColor.rgb = texture(uTexture, gl_FragCoord.xy).rgb;
    vec3 v = clamp(outColor.rgb, vec3(0), vec3(1));

    //v = 0.5 + pow(abs(v - 0.5)*2, vec3(1.0)) * sign(v - 0.5) / 2;

    outColor.rgb = v;
    outColor.a = 1;
}
