#version 410 core

// Daze

layout(location = 0) out vec4 fragColor;

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {
	float slowerTime = time / 10.0f;

	vec2 p = 2.0 * (gl_FragCoord.xy / resolution.xy) - 1.0;
	vec2 m = 2.0 * mouse - 1.0;

	float color = 0.0;
	color += sin(p.x * cos(slowerTime)) * 30.0 + cos(p.y * cos(slowerTime)) * 50.0;
	color += cos(p.x * sin(slowerTime)) * 70.0 + sin(p.y * sin(slowerTime)) * 20.0;
	color += sin(p.y * cos(slowerTime)) * 60.0 + cos(p.x * cos(slowerTime)) * 80.0;
	color += cos(p.y * sin(slowerTime)) * 90.0 + sin(p.y * sin(slowerTime)) * 10.0;
	
	fragColor = vec4(vec3((sin(color * slowerTime) + 1.0) / 2.0,
					 color,
					(cos(color * 2.3) + 1.0) / 2.0), 1.0);
}