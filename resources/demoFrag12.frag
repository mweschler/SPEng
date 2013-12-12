#version 120

uniform sampler2D tex;
uniform vec3 lightDir;
uniform vec4 lightColor;
uniform vec4 ambient;
uniform vec3 diffuse;

varying vec3 vertexNormal;
varying vec2 uv;

void main()
{
    float cosAngIncidence = dot(normalize(vertexNormal), lightDir);
    cosAngIncidence = clamp(cosAngIncidence, 0, 1);
    vec4 texColor = texture2D(tex, uv);
    gl_FragColor = (texColor * lightColor * cosAngIncidence) + (texColor * ambient);
}