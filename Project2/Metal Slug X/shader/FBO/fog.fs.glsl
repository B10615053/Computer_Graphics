#version 410 core

uniform sampler2D tex;

out vec4 color;

in VS_OUT {
	vec2 texcoord;
} fs_in;
in vec2 pos;

void main(void) {
	vec4 texture_color = texture(tex, fs_in.texcoord);
	
	texture_color.a = (pos.y + 1.0) / 2.0;
	color = texture_color;
}