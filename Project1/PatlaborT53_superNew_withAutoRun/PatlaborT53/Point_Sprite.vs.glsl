#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform float time;
uniform vec2 mouse;
uniform mat4 proj_matrix;
uniform int plusOrMinus;

flat out vec4 starColor;

void main(void)
{
	vec4 newVertex = position;

	if(plusOrMinus == 0)
		newVertex.z -= time;
	else
		newVertex.z += time;

	newVertex.z = fract(newVertex.z);

	float size = (10.0 * newVertex.z);

	starColor = smoothstep(1.0, 7.0, size) * color;

	newVertex.z = (999.9 * newVertex.z) - 1000.0;
	gl_Position = proj_matrix * newVertex;
	gl_PointSize = size;
}