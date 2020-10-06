#version 410 core

out vec4 color;

uniform sampler2D tex_star;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float time;
uniform int plusOrMinus;

flat in vec4 starColor;

void main(void)
{
	vec2 coord = gl_PointCoord;

	if(plusOrMinus == 0)
		coord = mouse;

	color = starColor * texture(tex_star, coord);
	//if (color.a < 0.1)
	//	discard;

	if(plusOrMinus == 0) {
		highp int i = int(time);
		i %= 256;
		highp float fi = float(i);
		fi /= 255.0;

		vec2 p = 2.0 * (gl_FragCoord.xy / resolution.xy) - 1.0;
		vec2 m = 2.0 * mouse - 1.0;
		vec3 col = vec3(0.0);
		col = vec3(fi, 1.0 - fi, 0.0);

		if(abs(m.x - p.x) <= 0.097 && abs(m.y + p.y) <= 0.097) {
			color = vec4(1.0, 0, 0, 1);
		}
	}
}