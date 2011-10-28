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
varying float fogFactor;

void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition, 1);
	
	const float maxDepth = 600.0;
	const float threshold = 0.004; // ~ lsb
	const float rho = -log(threshold) / maxDepth;
	
	// fogFactor = max(0, min(1, gl_Position.w / maxDepth));
	fogFactor = exp(-rho * gl_Position.w);
	
	normal = inNormal;
	uv = inUv;
	tangent = inTangent;
}