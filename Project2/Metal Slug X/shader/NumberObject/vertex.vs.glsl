#version 410 core

// numberObject

layout (location = 0) in vec2 pos;
layout(location = 1) in int spriteIndex;

uniform mat4 um4mv;
uniform mat4 um4p;

out VertexData
{
	vec2 texcoord;
	flat int spriteIndex;
} vertexData;

out float posx;
out float posy;

float offsetX = 0.05;
vec2[] points = vec2[4](vec2(pos.x - offsetX, pos.y), vec2(pos.x + offsetX, pos.y), vec2(pos.x - offsetX, pos.y + 0.25), vec2(pos.x + offsetX, pos.y + 0.25));
vec2[] uv = vec2[4](vec2(0, 0), vec2(1, 0), vec2(0, 1), vec2(1, 1));

void main()
{
	gl_Position = um4p * um4mv * vec4(points[gl_VertexID], 0.0, 1.0);
	vertexData.texcoord = uv[gl_VertexID];
	posx = pos.x;
	posy = pos.y;
	vertexData.spriteIndex = spriteIndex;
}
