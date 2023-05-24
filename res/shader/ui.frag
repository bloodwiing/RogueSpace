#version 440

in vec2 v_currentPos;
in vec2 v_texCoord;

out vec4 o_fragColor;

uniform sampler2D Texture0;

void main() {
    o_fragColor = texture(Texture0, v_texCoord);
}