#version 440

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec2 texCoord;

out vec2 v_currentPos;
out vec2 v_texCoord;

uniform mat3 Frame;

void main() {
    v_currentPos = vec2(Frame * vec3(pos, 1.0));

    gl_Position = vec4(v_currentPos, 0.0, 1.0);
    v_texCoord = texCoord;
}