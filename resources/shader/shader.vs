#version 330 core

uniform vec4 u_lightPosition;
uniform mat4 u_MatrixProjection;
uniform mat4 u_MatrixView;
uniform mat4 u_MatrixModel;

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec4 a_normal;
layout (location = 2) in vec2 a_textureCoordinate;

out vec2 v_textureCoordinate;
out float v_brightness;


void main ()
{
    gl_Position = u_MatrixProjection * u_MatrixView * u_MatrixModel * a_position;

    vec4 lightDirection = normalize(u_lightPosition - a_position);
    v_brightness = clamp(dot(lightDirection, a_normal), 0.2, 1.0);
    v_textureCoordinate = a_textureCoordinate;
}
