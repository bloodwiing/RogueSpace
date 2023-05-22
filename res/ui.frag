#version 440

in vec2 v_currentPos;
in vec2 v_texCoord;

out vec4 o_fragColor;

uniform sampler2D Diffuse0;
uniform vec4 DiffuseFactor;

uniform sampler2D Specular0;
uniform float MetallicFactor;
uniform float RoughnessFactor;

uniform vec4 LightColour;
uniform vec3 LightPos;
uniform vec3 CameraPos;

void main() {
    o_fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}