// Fragment Shader file "base.frag"

#version 120

varying vec3 normal;
varying vec2 uv;

varying float fogFactor;

uniform sampler2D sDiffuse;
uniform sampler2D sSpecular;

void main(void)
{
	const vec4 fogColor = vec4(0.0000398107, 0.2474041117391, 0.562703, 1.0);
		
	vec4 color = texture2D(sDiffuse, uv);	
	
	gl_FragData[0] = color * fogFactor + fogColor * (1-fogFactor);
}