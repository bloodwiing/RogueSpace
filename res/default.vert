#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 colour;
layout (location = 3) in vec2 texCoord;

out vec3 v_currentPos;
out vec3 v_normal;
out vec2 v_texCoord;

uniform mat4 CameraMatrix;

uniform mat4 Model;
uniform mat4 Translation;
uniform mat4 Rotation;
uniform mat4 Scale;

void main() {
    v_currentPos = vec3(Model * Translation * Rotation * Scale * vec4(pos, 1.0));

    gl_Position = CameraMatrix * vec4(v_currentPos, 1.0);
    v_texCoord = texCoord;

    v_normal = vec3(normalize(Model * vec4(normal, 1.0)));
}