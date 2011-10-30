// Fragment Shader file "base.frag"

#version 120

varying vec3 normal;
varying vec2 uv;
varying vec3 tangent;

varying float fogFactor;

uniform sampler2D sDiffuse;
uniform sampler2D sSpecular;

void main(void)
{
	const vec4 fogColor = vec4(0.0000398107, 0.2474041117391, 0.562703, 1.0);
		
	vec3 lightDirection = normalize(vec3(1, 1, 1));

	vec4 color = texture2D(sDiffuse, uv);
	// vec4 specColor = texture2D(sSpecular, uv);
	
	float diffuseFactor = max(0.0, dot(normal, lightDirection));
	float ambient = 0.1;
	
	vec4 c = diffuseFactor * color + color * ambient;// + specColor * 0.5;
	c.a = 1.0;
	
	gl_FragData[0] = c * fogFactor + fogColor * (1-fogFactor);

}