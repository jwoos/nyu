/*
File Name: "vshader53.glsl":
Vertex shader:
  - Per vertex shading for a single point light source;
    distance attenuation is Yet To Be Completed.
  - Entire shading computation is done in the Eye Frame.
*/

#version 150

in vec4 vPosition;
in vec3 vNormal;
out vec4 color;

uniform vec4 ambientProduct, diffuseProduct, specularProduct;
uniform mat4 modelView;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec4 lightPosition;   // Must be in Eye Frame
uniform float shininess;

uniform float constAtt;  // Constant Attenuation
uniform float linearAtt; // Linear Attenuation
uniform float quadAtt;   // Quadratic Attenuation

void main() {
	// Transform vertex  position into eye coordinates
	vec3 pos = (modelView * vPosition).xyz;

	vec3 L = normalize(lightPosition.xyz - pos);
	vec3 E = normalize(-pos);
	vec3 H = normalize(L + E);

	// Transform vertex normal into eye coordinates
	// vec3 N = normalize( ModelView*vec4(vNormal, 0.0) ).xyz;
	vec3 N = normalize(normalMatrix * vNormal);

	/*--- To Do: Compute attenuation ---*/
	float attenuation = 1.0;

	// Compute terms in the illumination equation
	vec4 ambient = ambientProduct;

	float d = max(dot(L, N), 0.0);
	vec4 diffuse = d * diffuseProduct;

	float s = pow(max(dot(N, H), 0.0), shininess);
	vec4 specular = s * specularProduct;

	if (dot(L, N) < 0.0) {
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}

	gl_Position = projection * modelView * vPosition;

	/*--- attenuation below must be computed properly ---*/
	color = attenuation * (ambient + diffuse + specular);
}
