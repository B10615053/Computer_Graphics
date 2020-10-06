#version 410 core

layout(location = 0) out vec4 fragColor;

// marco

in VertexData
{
	vec2 texcoord;
	flat int spriteIndex;
} vertexData;

uniform sampler2DArray tex;
uniform float blinkingcounter;
uniform vec3 pos3d;

void main()
{
	//fragColor = texture(tex, vec3(vertexData.texcoord, vertexData.spriteIndex));
	vec2 p = 2.0 * (gl_FragCoord.xy / vec2(600, 440)) - 1.0;
	//p = vertexData.texcoord;
	vec4 color = texture(tex, vec3(vertexData.texcoord, vertexData.spriteIndex));
	
	if(blinkingcounter >= 0.0) {
		float alpha = (sin(blinkingcounter) + 1.0) / 2.0;
		if(color.a <= 0.0)
			alpha = 0.0f;
		
		if(color.r + color.g + color.b <= 0.07)
			fragColor = vec4(vec3(0.9, 0.9, 0.9), 0.0);
		else
			fragColor = vec4(color.rgb, alpha);
	}
	else
		fragColor = color;
	
	if(blinkingcounter > -2) {
		if(color.r + color.g + color.b <= 0.07)
			fragColor = vec4(vec3(0.9, 0.9, 0.9), 0.0);
		else {
			vec3 normal = vec3(0.0, 0.0, -1.0);
			vec3 light = normalize(vec3(p.x - pos3d.x, p.y + pos3d.y, pos3d.z * 0.7));
			float innerProduct = (normal.x * light.x) + (normal.y * light.y) + (normal.z * light.z);
			float cos_theta = tan(innerProduct * (3.1416 / 2.0));
			
			fragColor.rgb += cos_theta;
			
			/*
			float xie = ((pos3d.x - p.x) * (pos3d.x - p.x)) + ((pos3d.y - p.y) * (pos3d.y - p.y)) + ((pos3d.z) * (pos3d.z));
			float chang = ((pos3d.x - p.x) * (pos3d.x - p.x)) + ((pos3d.y - p.y) * (pos3d.y - p.y));
			float angle = acos(chang / xie);
			fragColor.rgb += clamp(angle * 1.5 - 1.5, 0.0, 1.0);
			*/
		}
	}
}