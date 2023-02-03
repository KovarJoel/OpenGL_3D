#version 330 core

in vec3 uColor;
in vec2 TexCoord;
out vec4 FragmentColor;

uniform float mixValue;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragmentColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue) * vec4(uColor, 1.0f);
}