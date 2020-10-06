#version 410 core

layout(location = 0) out vec4 fragColor;

// Distorted

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

#define PI 	3.1415926

float random (vec2 st) {
	st = st * 2.0 - 1.0;
	st *= time * 0.2;

	return pow(cos(st.x * st.y), sin(st.y / (st.x)));
}

float distanceToLine(vec2 p1, vec2 p2, vec2 point) {
    float a = p1.y - p2.y;
    float b = p2.x - p1.x;

    return abs(a * point.x + b * point.y + p1.x * p2.y - p2.x * p1.y) / sqrt(a * a + b * b);
}

float distanceToSeg(vec2 p1, vec2 p2, vec2 point) {
	float cross = (p2.x - p1.x) * (point.x - p1.x) + (p2.y - p1.y) * (point.y - p1.y);
	if(cross <= 0)
		return sqrt( (point.x - p1.x) * (point.x - p1.x) + (point.y - p1.y) * (point.y - p1.y) );
		
	float d2 = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
	if(cross >= d2)
		return sqrt( (point.x - p2.x) * (point.x - p2.x) + (point.y - p2.y) * (point.y - p2.y) );
	
	float r = cross / (d2 + 0.000001);
	float px = p1.x + (p2.x - p1.x) * r;
	float py = p1.y + (p2.y - p1.y) * r;
	
	return sqrt( (point.x - px) * (point.x - px) + (point.y - py) * (point.y - py) );
}

void main(void) {
    //vec2 position = gl_FragCoord.xy - resolution * 0.5;
	vec2 p = 2.0 * ( gl_FragCoord.xy / resolution.xy ) - 1.0;
	vec2 m = 2.0 * mouse - 1.0;
	
	float col, row, dis;
	vec4 color = vec4(0.0, 1.0, 0.0, 0.5);
	
	float t = sin(time / 200.0);
	
	for(col = -10.0; col <= 10.0; col += 0.1) {
		dis = distanceToLine(vec2(col + t, -1.0), vec2(col + t * 3, 1.0), p);
		if(dis < 0.007) {
			color = vec4(vec3(1.0), 1.0 - dis * 100);
		}
	}
	
	for(row = -10.0; row <= 10.0; row += 0.1) {
		dis = distanceToLine(vec2(-1.0, row - t * 3), vec2(1.0, row - t), p);
		if(dis < 0.007) {
			color = vec4(vec3(1.0), 1.0 - dis * 100);
		}
	}
	
	dis = (p.x - m.x) * (p.x - m.x) + (p.y + m.y) * (p.y + m.y);
	if(dis < 1.0 - abs(t)) {
		if(color != vec4(0.0, 1.0, 0.0, 0.5))
			color = vec4(vec3(1.0), 1 - dis);
	}
	else {
		color += vec4(vec3(1.0), 1.0 - abs(t));
	}
	
    fragColor = color;
}