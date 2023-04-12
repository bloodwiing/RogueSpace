#version 330 core

layout location = 0) in vec3 pos

uniform ma4 Model;
uniform mat4 CameraMatrix

void main(

    gl_Position = CameraMatrix * Model  vec4(pos, 1.0)
}
