#version 410 core

layout(location = 0) out vec4 fragColor;

// Black hole

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float rand(vec2 n) { return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453); }

float noise(vec2 p) {
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);
	
	float res = mix(
		mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
		mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return res*res;
}

void main(void) {
	vec2 p = 2.0 * (gl_FragCoord.xy / resolution.xy) - 1.0;
	vec2 m = 2.0 * mouse - 1.0;
	vec3 col = vec3(0.0);
	float diff = abs(length(p) - length(m));
	col = mix(vec3(0.0), vec3(1.0), 120.9);

	float gap;
	float alpha = 1.0;
	for(gap = 0.000; gap <= 1.0; gap += 0.001) {
		if(diff <= gap) {
			fragColor = vec4(col, alpha);
			break;
		}

		alpha -= 0.001;
	}
	
	float density = abs(m.x - p.x);
	if(density <= 0.097)
		fragColor += vec4(density);
	
	density = abs((m.y + p.y));
	if(density <= 0.097)
		fragColor += vec4(density);
}