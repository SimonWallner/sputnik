// Fragment Shader textLabel.frag

#version 120

varying vec2 uv;

uniform sampler2D sDiffuse;
varying float fogFactor;

void main(void)
{
	const vec4 fogColor = vec4(0.0000398107, 0.2474041117391, 0.562703, 1.0);

	vec4 c = 1 - texture2D(sDiffuse, uv);
	vec4 colour = vec4(c.r, c.r, c.r, 1);
	gl_FragData[0] = colour * fogFactor + fogColor * (1-fogFactor);
}