#version 410 core

uniform sampler2D tex;

out vec4 color;

in VS_OUT {
	vec2 texcoord;
} fs_in;
in vec2 pos;

void main(void) {
	vec4 texture_color = texture(tex, fs_in.texcoord);
	
	if(texture_color.r + texture_color.g + texture_color.b <= 0.7) {
		if(texture_color.b >= texture_color.g && texture_color.b >= texture_color.r) {
			texture_color.r = clamp(texture_color.r - 1.0, 0.0, 1.0);
			texture_color.g = clamp(texture_color.g - 1.0, 0.0, 1.0);
		}
		
		else if(texture_color.r >= texture_color.g && texture_color.r >= texture_color.b) {
			texture_color.b = clamp(texture_color.b - 1.0, 0.0, 1.0);
			texture_color.g = clamp(texture_color.g - 1.0, 0.0, 1.0);
		}
			
		else if(texture_color.g >= texture_color.r && texture_color.g >= texture_color.b) {
			texture_color.b = clamp(texture_color.b - 1.0, 0.0, 1.0);
			texture_color.r = clamp(texture_color.r - 1.0, 0.0, 1.0);
		}
	}
	
	texture_color.a = (pos.y + 1.0) / 2.0;
	color = texture_color;
}