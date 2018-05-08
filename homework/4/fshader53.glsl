/*
File Name: "fshader53.glsl":
           Fragment Shader
*/

#version 150

uniform int flagFogType;
uniform bool flagWire;
uniform bool flagFloorTexture;
uniform bool flagSphereTexture;
uniform bool flagTextureType;
uniform bool flagLattice;

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

	if (flagLattice) {
		if (fract(4 * fTexture2d.x) < 0.35 && fract(4 * fTexture2d.y) < 0.35) {
			discard;
		}
	}

	if (flagFloorTexture) {
		outColor = texture(texture2d, fTexture2d) * outColor;
	}

	if (flagSphereTexture && !flagWire) {
		if (!flagTextureType) {
			// stripe
			outColor = texture(texture1d, fTexture1d) * outColor;
		} else {
			// checker
			if (texture(texture2d, fTexture2d).r == 0) {
				outColor = vec4(0.9, 0.1, 0.1, 1) * outColor;
			} else {
				outColor = texture(texture2d, fTexture2d) * outColor;
			}
		}
	}

	if (flagFogType > 0) {
		float fogDistance = gl_FragCoord.z / gl_FragCoord.w;

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
