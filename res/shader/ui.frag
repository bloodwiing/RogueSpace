#version 440

in vec2 v_currentPos;
in vec2 v_texCoord;

out vec4 o_fragColor;

uniform sampler2D Texture0;

uniform vec4 Multiply = vec4(1.0);
uniform vec4 Add = vec4(0.0);

void main() {
    o_fragColor = texture(Texture0, v_texCoord) * Multiply + Add;
}