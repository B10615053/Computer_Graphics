// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible

// Transparent

#version 430
struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
};

uniform MaterialInfo Material;
out vec4 vFragColor;

void main(void)
{
    // No ambient, diffuse, or specular color used
	// alpha is set to 0.4
    vFragColor = vec4(Material.Kd, 0.4);
}
	
    