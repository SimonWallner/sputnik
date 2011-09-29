// vertex Shader base.vert

#version 120

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inUv;
attribute vec3 inTangent;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec3 normal;
varying vec2 uv;
varying vec3 tangent;

void main(void)
{
	// gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition, 1);
	gl_Position = projectionMatrix * viewMatrix * vec4(inPosition, 1);
	
	// gl_Position = vec4(inPosition, 1);

	normal = inNormal;
	uv = inUv;
	tangent = inTangent;
}