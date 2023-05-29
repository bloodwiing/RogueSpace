#version 440

in vec2 v_currentPos;
in vec2 v_relCoord;
in vec2 v_texCoord;

out vec4 o_fragColor;

uniform sampler2D Texture0;

uniform vec4 Multiply = vec4(1.0);
uniform vec4 Add = vec4(0.0);

uniform float CropLeft = 0.0;
uniform float CropBottom = 0.0;
uniform float CropRight = 1.0;
uniform float CropTop = 1.0;

void main() {
    if (v_relCoord.x > CropRight || v_relCoord.x < CropLeft || v_relCoord.y > CropTop || v_relCoord.y < CropBottom)
        discard;

    o_fragColor = texture(Texture0, v_texCoord) * Multiply + Add;
}