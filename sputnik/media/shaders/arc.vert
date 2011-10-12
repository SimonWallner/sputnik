// vertex Shader arch.vert

#version 120

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inUv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform int instance;
uniform vec3 start;
uniform vec3 end;

varying vec3 normal;
varying vec2 uv;

void main(void)
{
	float t = instance / 200.0;
	vec3 translate = end * t + start * (1 - t);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition + translate, 1);

	normal = inNormal;
	uv = inUv;
}