// Fragment Shader file "arch.frag"

#version 120

void main(void)
{
	gl_FragData[1] = vec4(0.1, 1, 1, 0.2);
	gl_FragData[0] = gl_FragData[1];
}