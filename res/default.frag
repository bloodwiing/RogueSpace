#version 330 core

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_currentPos;

out vec4 o_fragColor;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform vec4 LightColour;
uniform vec3 LightPos;
uniform vec3 CameraPos;

void main() {
    float ambient = 0.10;

    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(LightPos - v_currentPos);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularLight = 0.50;
    vec3 viewDirection = normalize(CameraPos - v_currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8.0);
    float specular = specularLight * specularAmount;

    o_fragColor = texture(Texture0, v_texCoord) * LightColour * (diffuse + ambient) + texture(Texture1, v_texCoord).r * specular;
}