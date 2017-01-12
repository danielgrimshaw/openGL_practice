#version 400 core
out vec4 o_color;

uniform vec2 u_resolution; // Canvas size (width, height)
uniform vec2 u_mouse; // Mouse position in screen pixels
uniform float u_time; // Run time in seconds

float random(vec2 st) {
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 453758.5453123);
}

void main() {
	vec2 st = vec2(gl_FragCoord.y, 0.0)/u_resolution;

	st *= 10.0;
	vec2 iPos = floor(st);
	vec2 fPos = fract(st);

	vec3 color = vec3(random(iPos));

	color = vec3(fPos, 0.0);
	o_color = vec4(color, 1.0);
}