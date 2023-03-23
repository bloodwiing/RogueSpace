#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_currentPos;

uniform mat4 Model;
uniform mat4 CameraMatrix;

void main() {
    v_currentPos = vec3(Model * vec4(pos, 1.0));

    gl_Position = CameraMatrix * vec4(v_currentPos, 1.0);
    v_texCoord = texCoord;

    v_normal = vec3(normalize(Model * vec4(normal, 1.0)));
}