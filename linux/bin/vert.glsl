#version 400 core
precision highp float;

layout(location = 0) in vec3 position;

void main() {
	gl_Position = vec4(position.x, position.y, position.z, 1.0f);
}