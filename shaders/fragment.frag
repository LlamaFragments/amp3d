#version 150

in vec3 Color;

out vec4 finalColor;

void main()
{

	finalColor = vec4(Color, 1.0);
}