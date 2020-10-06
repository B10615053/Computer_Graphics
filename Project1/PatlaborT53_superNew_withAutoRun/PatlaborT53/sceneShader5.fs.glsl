#version 410 core

layout(location = 0) out vec4 fragColor;

// Sine waves

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float rand(vec2 n) {  return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453); }

float noise(vec2 p){
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);
	
	float res = mix(
		mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
		mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return res*res;
}

void main(void)
{
  float t = 0.1 * time;
  vec3 rColor = vec3(0.9, 0.0, 0.3);
  vec3 gColor = vec3(0.0, 0.9, 0.3);
  vec3 bColor = vec3(0.0, 0.3, 0.9);
  vec3 yColor = vec3(0.5, 0.5, 0.0);
  vec3 iColor = vec3(0.5, 1.0, 1.0);
  vec3 hColor = vec3(0.0, 0.0, 1.0);

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / resolution.y;

  float mx = (mouse.x * 2.0) - 1.0;
  float my = (mouse.y * 2.0) - 1.0;
  float xoffset = -1.6;

  float a = sin(p.x * 5.0 - mx * 5.0  + xoffset + t) / 2.0 + my;
  float b = sin(p.x * 5.0 - mx * 7.0  + xoffset + t) / 3.0 + my;
  float c = sin(p.x * 5.0 - mx * 9.0  + xoffset + t) / 4.0 + my;
  float d = sin(p.x * 5.0 - mx * 11.0 + xoffset + t) / 5.0 + my;
  float e = sin(p.x * 5.0 - mx * 10.0 + xoffset + t) / 5.0 + my;

  float f = 0.01 / abs(p.y + a);
  float g = 0.01 / abs(p.y + b);
  float h = 0.01 / abs(p.y + c);
  float i = 0.01 / abs(p.y + d);

  vec3 destColor = rColor * f + gColor * g + bColor * h + yColor * i;
  fragColor = vec4(destColor, 0.5);

  p = (gl_FragCoord.xy / resolution.xy);
  vec2 m = vec2(time / 10., 0.0) ;

  if(mouse.x < 0.5)
	fragColor += vec4(vec3(noise(p * 2.5 + m), noise(p * 1.25 + m) , noise(p * 5.0 + m)), 0.5 );
  else
	fragColor += vec4(vec3(noise(p * 2.5 - m), noise(p * 1.25 - m) , noise(p * 5.0 - m)), 0.5 );
}