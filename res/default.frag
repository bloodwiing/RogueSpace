#version 330 core

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_currentPos;

out vec4 o_fragColor;

uniform sampler2D TextureSampler;
uniform vec4 LightColour;
uniform vec3 LightPos;

void main() {
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(LightPos - v_currentPos);

    float diffuse = max(dot(normal, lightDirection), 0.0);

    o_fragColor = texture(TextureSampler, v_texCoord) * LightColour * diffuse;
}