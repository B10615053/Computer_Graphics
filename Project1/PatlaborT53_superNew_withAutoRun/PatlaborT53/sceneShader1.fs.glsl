#version 410 core

// XY coordinate

layout(location = 0) out vec4 fragColor;

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

vec2 p1 = vec2(-0.4,  0.3);
vec2 p2 = vec2(-0.1,  0.3);
vec2 p3 = vec2(-0.1,  0.0);
vec2 p4 = vec2(-0.1, -0.3);
vec2 p5 = vec2(-0.4, -0.3);
vec2 p6 = vec2(-0.4,  0.0);

vec2 b1 = vec2(-0.4 - 0.4,  0.3);
vec2 b2 = vec2(-0.1 - 0.4,  0.3);
vec2 b3 = vec2(-0.1 - 0.4,  0.0);
vec2 b4 = vec2(-0.1 - 0.4, -0.3);
vec2 b5 = vec2(-0.4 - 0.4, -0.3);
vec2 b6 = vec2(-0.4 - 0.4,  0.0);

vec2 q1 = vec2( 0.1,  0.3);
vec2 q2 = vec2( 0.4,  0.3);
vec2 q3 = vec2( 0.4,  0.0);
vec2 q4 = vec2( 0.4, -0.3);
vec2 q5 = vec2( 0.1, -0.3);
vec2 q6 = vec2( 0.1,  0.0);

vec2 d1 = vec2( 0.1 + 0.4,  0.3);
vec2 d2 = vec2( 0.4 + 0.4,  0.3);
vec2 d3 = vec2( 0.4 + 0.4,  0.0);
vec2 d4 = vec2( 0.4 + 0.4, -0.3);
vec2 d5 = vec2( 0.1 + 0.4, -0.3);
vec2 d6 = vec2( 0.1 + 0.4,  0.0);

void main( void ) {
	vec2 p = 2.0 * ( gl_FragCoord.xy / resolution.xy ) - 1.0;
	vec2 m = mouse;
	//vec2 m = 2.0 * mouse - 1.0;
	
	if(m.x >= 1.0)
		m.x = 0.99;
	m.y = abs(m.y);
	if(abs(m.y) >= 1.0)
		m.y = 1.0;
	
	float w = 0.02;
	vec4 col = vec4((sin(cos(p.x - p.y + (time / 50.0)) * ((2.0 * mouse.x - 1.0) - (2.0 * mouse.y - 1.0)) * 50.43) + 1.0) / 2.0);
	
	vec2 commaLoc = vec2(-0.05, -0.30);
	if(distanceToSeg(commaLoc, commaLoc, p) <= 0.015)
		col = vec4(vec3(1.0), 1.0 - col.w);
	
	if(distanceToSeg(vec2(commaLoc.x + 0.005, commaLoc.y - 0.01), vec2(commaLoc.x - 0.01, commaLoc.y - 0.03), p) <= 0.006)
		col = vec4(vec3(1.0), 1.0 - col.w);

	highp int counter = int(time / 10.0);
	counter %= 100;
	
	highp int mx = int(m.x * 100.0);
	highp int my = int(m.y * 100.0);
	
	//int i = counter / 10;
	int i = mx / 10;
	
	// ========================================================================================
	
	//i = counter % 10;
	i = mx / 10;
	
	if(distanceToSeg(b2, b1, p) < w) {
		if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(b2, b3, p) < w) {
		if(i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(b4, b3, p) < w) {
		if(i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(b4, b5, p) < w) {
		if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(b6, b5, p) < w) {
		if(i == 0 || i == 2 || i == 6 || i == 8) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(b6, b1, p) < w) {
		if(i == 0 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(b6, b3, p) < w) {
		if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	// ==========================================================================================
	
	//i = counter % 10;
	i = mx % 10;
	
	if(distanceToSeg(p2, p1, p) < w) {
		if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(p2, p3, p) < w) {
		if(i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(p4, p3, p) < w) {
		if(i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(p4, p5, p) < w) {
		if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(p6, p5, p) < w) {
		if(i == 0 || i == 2 || i == 6 || i == 8) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(p6, p1, p) < w) {
		if(i == 0 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(p6, p3, p) < w) {
		if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	// ========================================================================================
	
	i = my / 10;
	
	if(distanceToSeg(q2, q1, p) < w) {
		if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(q2, q3, p) < w) {
		if(i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(q4, q3, p) < w) {
		if(i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(q4, q5, p) < w) {
		if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(q6, q5, p) < w) {
		if(i == 0 || i == 2 || i == 6 || i == 8) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(q6, q1, p) < w) {
		if(i == 0 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(q6, q3, p) < w) {
		if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	// ========================================================================================
	
	//i = counter % 10;
	i = my % 10;
	
	if(distanceToSeg(d2, d1, p) < w) {
		if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(d2, d3, p) < w) {
		if(i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(d4, d3, p) < w) {
		if(i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(d4, d5, p) < w) {
		if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(d6, d5, p) < w) {
		if(i == 0 || i == 2 || i == 6 || i == 8) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(d6, d1, p) < w) {
		if(i == 0 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	if(distanceToSeg(d6, d3, p) < w) {
		if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9) {
			col = vec4(vec3(1.0), 1.0 - col.w);
		}
	}
	
	fragColor = col;
}