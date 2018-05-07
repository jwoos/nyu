/*
File Name: "fshader53.glsl":
           Fragment Shader
*/

#version 150

uniform int flagFogType;
uniform bool flagFloorTexture;

uniform vec4 fogColor;
uniform float fogStart;
uniform float fogEnd;
uniform float fogDensity;

in vec4 color;
out vec4 fColor;


void main(void) {
	fColor = color;

	float fogDistance = gl_FragCoord.z / gl_FragCoord.w;

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

		fColor = mix(fogColor, color, clamp(fog, 0, 1));
	}
}
