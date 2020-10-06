// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible

// Colorful

#version 430
struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
};

uniform int partNum;
uniform MaterialInfo Material;
out vec4 vFragColor;

//lighting color
vec4    ambientColor = vec4(0.1,0.1,0.1,1);
vec4    diffuseColor = vec4(0.8,0.8,0.8,1);   
vec4    specularColor = vec4(0.4,0.4,0.4,1);

in vec3 vVaryingNormal;
in vec3 vVaryingLightDir;
in vec2 UV;
float Shininess = 128.0;//for material specular

void main(void)
{ 

	switch (partNum) {
		case 0:
			diffuseColor = vec4(0.5, 0.2, 0.1, 1);
			break;
		case 1:
			diffuseColor = vec4(1, 0.4, 0.22, 1);
			break;
		case 2:
			diffuseColor = vec4(0.1, 0.89, 0.128, 1);
			break;
		case 3:
			diffuseColor = vec4(1, 0.464, 0.0, 1);
			break;
		case 4:
			diffuseColor = vec4(0.76, 0.0, 0.9, 1);
			break;
		case 5:
			diffuseColor = vec4(0.56, 0.34, 1, 1);
			break;
		case 6:
			diffuseColor = vec4(0.88, 0.7112, 0.09, 1);
			break;
		case 7:
			diffuseColor = vec4(0.33, 0.619, 1, 1);
			break;
		case 8:
			diffuseColor = vec4(0.78, 0.0, 0.0, 1);
			break;
		case 9:
			diffuseColor = vec4(0.96, 0.32, 0.67, 1);
			break;
		case 10:
			diffuseColor = vec4(0.2, 0.314, 1, 1);
			break;
		case 11:
			diffuseColor = vec4(0.5, 1, 0.192, 1);
			break;
		case 12:
			diffuseColor = vec4(0.82, 0.79, 0.12, 1);
			break;
		case 13:
			diffuseColor = vec4(0.4, 0.23, 0.98, 1);
			break;
	}

    // Dot product gives us diffuse intensity
    float diff = max(0.0, dot(normalize(vVaryingNormal),
					normalize(vVaryingLightDir)));

    // Multiply intensity by diffuse color, force alpha to 1.0
    vFragColor = diff * diffuseColor*vec4(Material.Kd,1);
    //vFragColor = diff * vec4(Material.Kd,0.4);

    // Add in ambient light
    vFragColor += ambientColor;

	//float grayscale_color = 0.299*vFragColor.r + 0.587*vFragColor.g + 0.114*vFragColor.b;
	//vFragColor = vec4(grayscale_color, grayscale_color, grayscale_color, 1.0);

    // Specular Light
    vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir),
								normalize(vVaryingNormal)));//反射角
    float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
    if(diff != 0) {
		spec = pow(spec, Shininess);
		vFragColor += specularColor*vec4(Material.Ka,1)*spec;
    }
}
	
    