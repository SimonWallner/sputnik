// Fragment Shader file "arch.frag"

#version 120

varying vec3 normal;
varying vec2 uv;
varying vec3 tangent;

uniform sampler2D sDiffuse;
uniform sampler2D sSpecular;

void main(void)
{
	gl_FragColor = vec4(0.1, 1, 1, 0.2);
}