// Fragment Shader file "star.frag"

#version 120

varying vec3 normal;
varying vec2 uv;
varying vec3 tangent;
varying float fogFactor;


void main(void)
{
	const vec4 fogColor = vec4(0.0000398107, 0.2474041117391, 0.562703, 1.0);
	gl_FragColor = vec4(1, 1, 1, 1) * fogFactor + fogColor * (1-fogFactor);
}