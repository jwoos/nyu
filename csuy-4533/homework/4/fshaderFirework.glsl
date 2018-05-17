#version 150


in vec4 fColor;
in vec4 fPosition;

out vec4 outColor;


void main(void) {
	if (fPosition.y < 0.1) {
		discard;
	}

	outColor = fColor;
}
