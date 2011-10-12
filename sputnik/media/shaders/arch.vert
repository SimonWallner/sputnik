// vertex Shader arch.vert

#version 120

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inUv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform int instance;

varying vec3 normal;
varying vec2 uv;

void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition + vec3(0, 0, -instance), 1);

	normal = inNormal;
	uv = inUv;
}