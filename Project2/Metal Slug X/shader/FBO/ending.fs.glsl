#version 410 core

uniform sampler2D tex;
uniform float pivot;

out vec4 color;

in VS_OUT {
	vec2 texcoord;
} fs_in;
in vec2 pos;

void main(void) {
	vec4 texture_color = texture(tex, fs_in.texcoord);
	
	// pivot from 3.0 to 0.0
	if(texture_color.r + texture_color.g + texture_color.b >= pivot) {
		texture_color = vec4(1.0);
	}
	
	color = texture_color;
}