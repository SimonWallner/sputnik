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
	// cure params
	const float tension = 2;
		
	float t = float(instance) / float(totalInstances); // [0, 1]
	
	vec3 direction = start - end;
	vec3 movedMid = midpoint - (direction * 0.5);
	
	float r = pow(t * 2 - 1, tension); //[0, 1]

	vec3 translate = (end + direction * t) * r + (movedMid + direction * t) * (1 - r);
		
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition + translate, 1);

	normal = inNormal;
	uv = inUv;
}