#version 330 core

in vec3 v_currentPos;
in vec3 v_normal;
in vec2 v_texCoord;
in float v_depth;

out vec4 o_fragColor;

uniform sampler2D Diffuse0;
uniform vec4 DiffuseFactor;

uniform sampler2D Specular0;
uniform float MetallicFactor;
uniform float RoughnessFactor;

uniform vec4 LightColour;
uniform vec3 LightPos;
uniform vec3 CameraPos;

vec4 pointLight() {
    vec3 lightVec = LightPos - v_currentPos;
    float dist = length(lightVec);
    float a = 3.0;
    float b = 0.7;
    float intensity = 1.0 / (a * dist * dist + b * dist + 1.0);

    float ambient = 0.10;

    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularLight = 0.50;
    vec3 viewDirection = normalize(CameraPos - v_currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8.0);
    float specular = specularLight * specularAmount;

    return (texture(Diffuse0, v_texCoord) * (diffuse * intensity + ambient) + texture(Specular0, v_texCoord).r * specular * intensity) * LightColour;
}

vec4 directLight() {
    float ambient = 0.10;

    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(vec3(1.0, 1.0, 1.0));
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularLight = 0.50;
    vec3 viewDirection = normalize(CameraPos - v_currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8.0);
    float specular = specularLight * specularAmount;

    return (texture(Diffuse0, v_texCoord) * (diffuse + ambient) + texture(Specular0, v_texCoord).r * specular) * LightColour;
}

vec4 spotLight() {
    float outerCone = 0.90;
    float innerCone = 0.95;

    float ambient = 0.10;

    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(LightPos - v_currentPos);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularLight = 0.50;
    vec3 viewDirection = normalize(CameraPos - v_currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8.0);
    float specular = specularLight * specularAmount;

    float angle = dot(vec3(0.0, -1.0, 0.0), -lightDirection);
    float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0, 1.0);

    return (texture(Diffuse0, v_texCoord) * (diffuse * intensity + ambient) + texture(Specular0, v_texCoord).r * specular * intensity) * LightColour;
}

vec4 unlit() {
    return texture(Diffuse0, v_texCoord);
}

float zNear = 0.1;
float zFar = 100.0;

float normalizedLinearDepth() {
    return (v_depth - zNear)/(zFar - zNear);
}

//const float[] ditherFilter = float[](
//    0.0, 5.0, 2.0, 5.0,
//    7.0, 4.0, 8.0, 4.0,
//    3.0, 6.0, 1.0, 6.0,
//    7.0, 4.0, 8.0, 4.0
//);
const float[] ditherFilter = float[](
    0.2, 0.6, 0.4, 0.6,
    0.8, 0.6, 1.0, 0.6,
    0.4, 0.6, 0.2, 0.6,
    1.0, 0.6, 0.8, 0.6
);

bool isDitherVisible() {
    int index = int(gl_FragCoord.x) % 4 + int(gl_FragCoord.y) % 4 * 4;
    float depth = normalizedLinearDepth();
    return depth * 500 > ditherFilter[index] && (10.0 - depth * 10) > ditherFilter[index];
}

void main() {
    if (!isDitherVisible())
        discard;
    o_fragColor = unlit();
}