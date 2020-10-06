#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform float time;
uniform mat4 proj_matrix;
uniform float angle;

flat out vec4 starColor;

float rand(vec2 n) {  return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453); }

void main(void)
{
	vec4 newVertex = position;

	//newVertex.z += time;
	//newVertex.z = fract(newVertex.z);
	
	newVertex.y += time * 5.0 * rand(vec2(23.4, -47.201));
	newVertex.x += angle;

	float size = (20.0 * newVertex.z * newVertex.z);

	starColor = smoothstep(1.0, 7.0, size) * color;

	newVertex.z = (999.9 * newVertex.z) - 1000.0;
	gl_Position = proj_matrix * newVertex;
	gl_PointSize = size;
}