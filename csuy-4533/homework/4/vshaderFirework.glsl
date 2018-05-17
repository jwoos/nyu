#version 150


uniform mat4 modelView;
uniform mat4 projection;
uniform float time;

in vec4 vColor;
in vec4 vVelocity;

out vec4 fColor;
out vec4 fPosition;


void main(void) {
	fColor = vColor;

	fPosition = vec4(
		0 + 0.001 * vVelocity.x * time,
		0.1 + 0.001 * vVelocity.y * time + 0.5 * (-4.9 * pow(10, -7)) * pow(time, 2),
		0 + 0.001 * vVelocity.z * time,
		1
	);

	gl_Position = projection * modelView * fPosition;
}
