#version 410 core

// Scene

layout (location = 0) in vec2 pos;
layout(location = 1) in int spriteIndex;

uniform mat4 um4mv;
uniform mat4 um4p;

out VertexData
{
	vec2 texcoord;
	flat int spriteIndex;
} vertexData;
out float isending;

vec2[] points = vec2[4](vec2(1.0, 1.0), vec2(-1.0, 1.0), vec2(1.0, -1.0), vec2(-1.0, -1.0));
vec2[] uv = vec2[4](vec2(0.0792 + pos.x, 1), vec2(0 + pos.x, 1), vec2(0.0792 + pos.x, 0), vec2(0 + pos.x, 0));

void main()
{ 
	if(pos.x < 0.0) {
		uv = vec2[4](vec2(1, 1), vec2(0, 1), vec2(1, 0), vec2(0, 0));
		isending = 10.0f;
	}
	else
		isending = -10.0f;

	gl_Position = um4p * um4mv * vec4(points[gl_VertexID], 0.0, 1.0);
	vertexData.texcoord = uv[gl_VertexID];
	vertexData.spriteIndex = spriteIndex;
}
