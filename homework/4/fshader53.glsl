/*
File Name: "fshader53.glsl":
           Fragment Shader
*/

#version 150

uniform int flagFogType;
uniform bool flagFloorTexture;
uniform bool flagSphereTexture;

uniform sampler2D texture2d;
uniform sampler1D texture1d;

uniform vec4 fogColor;
uniform float fogStart;
uniform float fogEnd;
uniform float fogDensity;

in vec4 fColor;
in float fTexture1d;
in vec2 fTexture2d;

out vec4 outColor;


void main(void) {
	outColor = fColor;

	float fogDistance = gl_FragCoord.z / gl_FragCoord.w;

	if (flagFloorTexture) {
		outColor = texture(texture2d, fTexture2d) * outColor;
	}

	if (flagSphereTexture) {
		outColor = texture(texture1d, fTexture1d) * outColor;
	}

	if (flagFogType > 0) {
		float fog;

		switch (flagFogType) {
			case 1:
				fog = (fogEnd - fogDistance) / (fogEnd - fogStart);
				break;

			case 2:
				fog = exp(-(fogDistance * fogDensity));
				break;

			case 3:
				fog = exp(-pow(fogDistance * fogDensity, 2));
				break;

			default:
				fog = 0;
		}

		outColor = mix(fogColor, outColor, clamp(fog, 0, 1));
	}
}
