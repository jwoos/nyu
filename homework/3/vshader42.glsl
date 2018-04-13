#version 150

in  vec3 vPosition;
in  vec3 vNormal;
out vec4 color;


uniform mat4 modelView;
uniform mat4 projection;


void main() {
	vec4 vPosition4 = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);
	vec4 vNormal4 = vec4(vNormal.r, vNormal.g, vNormal.b, 1.0);

    gl_Position = projection * modelView * vPosition4;

    color = vNormal4;
}
