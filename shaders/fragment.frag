#version 150

in vec3 Color;
in vec2 TexCoord;

out vec4 finalColor;

uniform sampler2D tex;

void main()
{

	finalColor = texture(tex, TexCoord) * vec4(Color, 1.0);
}