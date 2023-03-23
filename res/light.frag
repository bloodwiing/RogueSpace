#version 330 core

out vec4 o_fragColor;

uniform vec4 LightColour;

void main()
{
    o_fragColor = LightColour;
}