// Fragment Shader textLabel.frag

#version 120

varying vec2 uv;

uniform sampler2D sDiffuse;

void main(void)
{
	vec4 c = 1 - texture2D(sDiffuse, uv);
	gl_FragColor = vec4(c.r, c.r, c.r, 1);
}