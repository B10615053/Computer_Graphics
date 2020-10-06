// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible

// Black and white

#version 430
struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
};

uniform MaterialInfo Material;
out vec4 vFragColor;

//lighting color
vec4    ambientColor = vec4(0.1,0.1,0.1,0.4);
vec4    diffuseColor = vec4(0.8,0.8,0.8,0.1);   
vec4    specularColor = vec4(0.4,0.4,0.4,0.4);

in vec3 vVaryingNormal;
in vec3 vVaryingLightDir;
in vec2 UV;
float Shininess = 128.0; // for material specular

void main(void)
{ 
    // Dot product gives us diffuse intensity
    float diff = max(0.0, dot(normalize(vVaryingNormal),
					normalize(vVaryingLightDir)));

    // Multiply intensity by diffuse color, force alpha to 1.0
    vFragColor = diff * diffuseColor * vec4(Material.Kd, 1.0);

	// Gray scale formula
	float grayscale_color = 0.299 * vFragColor.r + 0.587 * vFragColor.g + 0.114 * vFragColor.b;

	// Simple thresholding
	if(grayscale_color >= 0.5)
		vFragColor = vec4(0.0, 0.0, 0.0, 1.0);
	else
		vFragColor = vec4(1.0, 1.0, 1.0, 1.0);
	
	// Add ambient color
	vFragColor += ambientColor;
}
	
    