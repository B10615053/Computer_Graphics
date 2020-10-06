#version 410 core

layout(location = 0) out vec4 fragColor;

// Shining star

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

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


void main( void ) {

	vec2 p = 2.0 * ( gl_FragCoord.xy / resolution.xy ) - 1.0;
	vec2 m = 2.0 * mouse - 1.0;
	
	float radius = sin(time / 100.0);
	float angle, aoff;
	vec2 endPoint;
	vec3 col = vec3(0.0);
	
	float s = abs(sin(time / 50.0));
	float c = abs(cos(time / 50.0));
	
	for(aoff = 0.0; aoff < 2 * 3.14; aoff += (3.14 / 8.0)) {
		for(angle = 0.0 + radius; angle < 2 * 3.14 + radius; angle += (3.14 / 4.0)) {
			endPoint = vec2(cos(angle) * radius, sin(angle) * radius);

			vec2 newM = vec2(cos(atan(m.y, m.x) + aoff) * length(m), sin(atan(m.y, m.x) + aoff) * length(m));
			if(distanceToSeg(endPoint, vec2(newM.x, -newM.y), p) <= 0.001)
				col = vec3((s + (aoff / (2 * 3.14))) / 2.0, (c + abs(newM.y)) / 2.0, abs(newM.x));
		}
	}

	fragColor = vec4(col, 1.0);
}