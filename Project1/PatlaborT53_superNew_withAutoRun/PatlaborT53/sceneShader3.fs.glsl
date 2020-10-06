#version 410 core

// Spinning

layout(location = 0) out vec4 fragColor;

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
	vec2 p = 2.0 * ( gl_FragCoord.xy / resolution.xy ) - 1.0;
	vec2 m = 2.0 * mouse - 1.0;
	vec4 color = vec4(vec3(0.0), 1.0);
	
	float linew = sqrt( (m.x * m.x) + (m.y * m.y) ) / 119.30472;
	
	float dis = distanceToSeg(vec2(m.x, -m.y), vec2(m.x, m.y), p);
	if(dis < linew) {
		color = vec4(1.0);
	}
	
	dis = distanceToSeg(vec2(-m.x, -m.y), vec2(-m.x, m.y), p);
	if(dis < linew) {
		color = vec4(1.0);
	}
	
	dis = distanceToSeg(vec2(m.x, -m.y), vec2(-m.x, -m.y), p);
	if(dis < linew) {
		color = vec4(1.0);
	}
	
	dis = distanceToSeg(vec2(m.x, m.y), vec2(-m.x, m.y), p);
	if(dis < linew) {
		color = vec4(1.0);
	}
	
	
	vec2 pt = m;
	if(m.x > 0)
		pt.x = -m.x;
	if(m.y > 0)
		pt.y = -m.y;
	
	float k;
	for(k = -0.01; k <= 0.01; k += 0.001) {
		dis = distanceToSeg(pt, vec2(-1.0 - k, -1.0 + k), p);
		if(dis < linew) {
			color = vec4(1.0);
		}
	}
	
	
	
	pt = m;
	if(m.x < 0)
		pt.x = -m.x;
	if(m.y < 0)
		pt.y = -m.y;
		
	for(k = -0.01; k <= 0.01; k += 0.001) {
		dis = distanceToSeg(pt, vec2(1.0 - k, 1.0 + k), p);
		if(dis < linew) {
			color = vec4(1.0);
		}
	}
	
	pt = m;
	if(m.x < 0)
		pt.x = -m.x;
	if(m.y > 0)
		pt.y = -m.y;
	
	for(k = -0.01; k <= 0.01; k += 0.001) {
		dis = distanceToSeg(pt, vec2(1.0 - k, -1.0 - k), p);
		if(dis < linew) {
			color = vec4(1.0);
		}
	}
	
	pt = m;
	if(m.x > 0)
		pt.x = -m.x;
	if(m.y < 0)
		pt.y = -m.y;
	
	for(k = -0.01; k <= 0.01; k += 0.001) {
		dis = distanceToSeg(pt, vec2(-1.0 - k, 1.0 - k), p);
		if(dis < linew) {
			color = vec4(1.0);
		}
	}
	
	float radius = 0.3, angle, cx1, cy1, xielv, Radius = 2.0, cx2, cy2;
	if(abs(m.x) < abs(m.y))
		radius = abs(m.x);
	else
		radius = abs(m.y);
	
	float t = tan(time / 130.0);
	
	for(angle = -PI + t; angle < PI + t; angle += PI / 32.0) {
		cx1 = cos(angle) * radius;
		cy1 = sin(angle) * radius;
		xielv = (-cx1) / (cy1);
		
		float xangle = atan(xielv);
		cx2 = cos(xangle) * Radius;
		cy2 = sin(xangle) * Radius;
		
		if(distanceToLine(vec2(cx1, cy1), vec2(cx2, cy2), p) <= 0.002) {
			color = vec4(0.5);
		}
	}
	
    fragColor = color;
}