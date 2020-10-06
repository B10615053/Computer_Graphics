#version 410 core

// scene

layout(location = 0) out vec4 fragColor;

in VertexData
{
	vec2 texcoord;
	flat int spriteIndex;
} vertexData;
in float isending;

uniform sampler2DArray tex;

void main()
{
	vec4 color = texture(tex, vec3(vertexData.texcoord, vertexData.spriteIndex));
	color.a = 1.0;
	
	if(isending > 0.0 && color.r + color.g + color.b < 0.0023) {
		vec2 p = 2.0 * ( gl_FragCoord.xy / vec2(600.0, 440.0) ) - 1.0;
		
		float q;
		for(q = -1.0; q <= 1.0; q += 0.04) {
			if(p.x <= q) {
				p.x = q;
				break;
			}
		}
		for(q = -1.0; q <= 1.0; q += 0.04) {
			if(p.y <= q) {
				p.y = q;
				break;
			}
		}
		
		color.rgb = vec3(abs(p.y), (sin(p.y * 2.0) + 1.0) / 2.0, 0.0);
	}
	
	fragColor = color;
}