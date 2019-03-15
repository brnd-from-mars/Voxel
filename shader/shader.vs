#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec4 colorIn;
uniform mat4 mvpMatrix;
uniform vec4 lightPosition;
out vec4 colorV;


void main ()
{
    gl_Position = mvpMatrix * position;

    float cosTheta = clamp(dot(normalize(lightPosition - position), normal), 0.0, 1.0);
    colorV = colorIn * cosTheta;
}
