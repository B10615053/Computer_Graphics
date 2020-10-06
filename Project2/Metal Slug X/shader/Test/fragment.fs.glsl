#version 410 core

layout(location = 0) out vec4 fragColor;

in VertexData
{
	vec2 pos;
	flat int spriteIndex;
} vertexData;

uniform sampler2DArray tex;

void main()
{
	fragColor = texture(tex, vec3(vertexData.pos, vertexData.spriteIndex));
}