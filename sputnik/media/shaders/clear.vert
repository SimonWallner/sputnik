// vertex Shader clear.vert

#version 120

attribute vec3 inPosition;
uniform mat4 modelMatrix;

void main(void)
{
	gl_Position = modelMatrix * vec4(inPosition, 1);
}