#version 410 core

layout(location = 0) out vec4 fragColor;

// Sun

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {
	float slowerTime = time / 100.f;
	
	vec2 p = 2.0*( gl_FragCoord.xy / resolution.xy ) -1.0;
	//p.x *= resolution.x/resolution.y;
	
	
	float s = sin(sin(slowerTime * 2.0) * 0.75);
    float c = cos(sin(slowerTime * 2.0));
    vec2 op = p * mat2(c, -s, s, c);

	float f = 0.0;
	float fs = 0.0;
	vec3 col = vec3(f);

	if (length(p) < length(2.0 * (mouse) - 1.0)) {
		f = atan(p.y, p.x) + slowerTime;
		fs = sin(f * 4.0);
		col = mix(vec3(1., 0.43, 0.0), vec3(0.93, 0.77, 0.01), fs);
	}
	else {
		f = atan(p.y, p.x) - slowerTime;
		fs = sin(f * 20.0);
		col = mix(vec3(1., 0.43, 0.0), vec3(0.2, 0.2, 0.2), fs);
		
		f = atan(p.y, p.x) + slowerTime;
		fs = sin(f * 20.0);
		col += mix(vec3(1., 0.43, 0.0), vec3(0.2, 0.2, 0.2), fs);
	}

	fragColor = vec4(col, 1.0);
}