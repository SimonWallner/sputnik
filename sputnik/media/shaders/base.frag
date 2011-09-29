// Fragment Shader file "base.frag"

#version 120

varying vec3 normal;
varying vec2 uv;
varying vec3 tangent;

uniform sampler2D sDiffuse;
uniform sampler2D sSpecular;

void main(void)
{
	vec3 lightDirection = normalize(vec3(1, 1, 1));

	vec4 color = texture2D(sDiffuse, uv);
	vec4 specColor = texture2D(sSecular, uv);
	
	float diffuseFactor = max(0.0, dot(normal, lightDirection));
	float ambient = 0.1;
	
	gl_FragColor = diffuseFactor * color + color * ambient + specColor * 0.5;
	gl_FragColor.a = 1.0;

}