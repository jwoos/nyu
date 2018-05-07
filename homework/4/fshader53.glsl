/*
File Name: "fshader53.glsl":
           Fragment Shader
*/

#version 150

uniform int flagFogType;

uniform vec4 fogColor;
uniform float fogStart;
uniform float fogEnd;
uniform float fogDensity;

in float fogDistance;
in vec4 color;
out vec4 fColor;


void main(void) {
	fColor = color;

	if (flagFogType > 0) {
		float fog;

		switch (flagFogType) {
			case 1:
				fog = clamp(fogDistance, fogStart, fogEnd) / (fogEnd - fogStart);
				//fog = (fogEnd - clamp(fogDistance, fogStart, fogEnd)) / (fogEnd - fogStart);
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
