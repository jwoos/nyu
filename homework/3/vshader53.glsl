/*
File Name: "vshader53.glsl":
Vertex shader:
  - Per vertex shading for a single point light source;
    distance attenuation is Yet To Be Completed.
  - Entire shading computation is done in the Eye Frame.
*/

#version 150

uniform bool flagLight;
uniform bool flagShading;

in vec4 vPosition;
in vec4 vColor;
in vec4 vNormal;
out vec4 color;

uniform mat4 modelView;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec4 lightPosition;   // Must be in Eye Frame
uniform vec4 globalLight;
uniform float shininess;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;

uniform float constAtt;  // Constant Attenuation
uniform float linearAtt; // Linear Attenuation
uniform float quadAtt;   // Quadratic Attenuation

void main() {
	gl_Position = projection * modelView * vPosition;

	if (flagLight) {
		// Transform vertex  position into eye coordinates
		vec3 pos = (modelView * vPosition).xyz;

		//vec3 L = normalize(lightPosition.xyz - pos);
		vec3 L = normalize(lightPosition.xyz);
		vec3 E = normalize(-pos);
		vec3 H = normalize(L + E);

		// Transform vertex normal into eye coordinates
		vec3 N;
		if (flagShading) {
			// smooth
			N = normalize(normalMatrix * vPosition.xyz);
		} else {
			// flat
			N = normalize(normalMatrix * vNormal.xyz);
		}

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

		color = globalLight + (attenuation * (ambient + diffuse + specular));
	} else {
		color = vColor;
	}
}
