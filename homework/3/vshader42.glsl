#version 150

in  vec3 vPosition;
in  vec3 vColor;
out vec4 color;


uniform mat4 modelView;
uniform mat4 projection;


void main() {
	vec4 vPosition4 = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);
	vec4 vColor4 = vec4(vColor.r, vColor.g, vColor.b, 1.0);

    gl_Position = projection * modelView * vPosition4;

    color = vColor4;
}
