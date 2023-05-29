#version 440

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec2 texCoord;

out vec2 v_currentPos;
out vec2 v_texCoord;

uniform mat3 Frame;

uniform vec2 UVCorner1;
uniform vec2 UVCorner2;

uniform mat3 UVMatrix;

void main() {
    v_currentPos = vec2(Frame * vec3(pos, 1.0));

    gl_Position = vec4(v_currentPos, 0.0, 1.0);

    v_texCoord = UVCorner1 + vec2(UVMatrix * vec3(texCoord, 1.0)) * (UVCorner2 - UVCorner1);
}