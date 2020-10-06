#version 410 core

// numberObject

layout(location = 0) out vec4 fragColor;

in VertexData
{
	vec2 texcoord;
	flat int spriteIndex;
} vertexData;

in float posx;
in float posy;

uniform sampler2DArray tex;

void main()
{
	vec4 color = vec4(1.0);
	
	if(posx < 0.5)
		color = texture(tex, vec3(vertexData.texcoord, vertexData.spriteIndex)).gbra;
	else
		color = texture(tex, vec3(vertexData.texcoord, vertexData.spriteIndex)).rgba;
	
	fragColor = color;
}