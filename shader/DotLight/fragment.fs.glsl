#version 410 core

// Dot light

layout(location = 0) out vec4 fragColor;

in VertexData
{
	vec2 texcoord;
	flat int spriteIndex;
} vertexData;

uniform sampler2DArray tex;

void main()
{
	vec4 color =  texture(tex, vec3(vertexData.texcoord, vertexData.spriteIndex)).rgba;
	fragColor = color;
}