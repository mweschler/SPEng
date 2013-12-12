#version 120

uniform mat3 normMatrix;
uniform mat4 mvp;

attribute vec4 vertex;
attribute vec2 texCords;
attribute vec3 normal;

varying vec2 uv;
varying vec3 vertexNormal;


void main(){
    vertexNormal = normalize(normMatrix *normal) ;
    uv = texCords; uv.y = 1.0f - uv.y;
    gl_Position = mvp * vertex;
}