// vertex Shader arch.vert

#version 120

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inUv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform int instance;
uniform int totalInstances;
uniform vec3 start;
uniform vec3 end;
uniform vec3 midpoint;

varying vec3 normal;
varying vec2 uv;

void main(void)
{
	float t = float(instance) / float(totalInstances);
	
	vec3 translate;
	if (t < 0.5)
	{
		translate = start * t + midpoint * (1 - t);		
	}
	else 
	{
		translate = midpoint * t + end * (1 - t);		
	}
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition + translate, 1);

	normal = inNormal;
	uv = inUv;
}