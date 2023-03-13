#version 330 core

in vec2 uv;

out vec4 FragColor;

void main() {
    FragColor = vec4(uv * 0.7 + 0.15, 1.0, 1.0);
}