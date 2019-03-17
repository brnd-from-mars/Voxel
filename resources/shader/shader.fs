#version 330 core

uniform sampler2D u_Texture;

in vec2 v_textureCoordinate;
in float v_brightness;

out vec4 o_Color;


void main ()
{
    o_Color = texture(u_Texture, v_textureCoordinate) * v_brightness;
}
