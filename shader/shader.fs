#version 330 core

in vec4 colorV;
out vec4 colorOut;


void main ()
{
    colorOut = colorV + vec4(0.0, 0.0, 0.0, 1.0);
}
