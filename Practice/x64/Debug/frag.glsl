#version 400 core
out vec4 o_color;

uniform vec2 u_resolution; // Canvas size (width, height)
uniform vec2 u_mouse; // Mouse position in screen pixels
uniform float u_time; // Run time in seconds

float random(float x) {
	return fract(sin(x)*1e4);
}

float random(vec2 st) {
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 453758.5453123);
}

float pattern(vec2 st, vec2 v, float t) {
	vec2 p = floor(st+v);
	return step(t, random(100.0+p*0.000001)+random(p.x)*0.5);
}

void main() {
	vec2 st = gl_FragCoord.xy/u_resolution.xy;
	st.x *= u_resolution.x/u_resolution.y;
	vec2 grid = vec2(100.0, 50.0);
	st *= grid;

	vec2 iPos = floor(st);
	vec2 fPos = fract(st);

	vec2 vel = vec2(u_time*2.0*max(grid.x, grid.y));
	vel *= vec2(u_mouse.y/u_resolution.y, 0.0) * random(1.0+iPos.y);

	vec2 offset = vec2(0.1, 0.0);

	vec3 color = vec3(0.0);
	color.r = pattern(st+offset, vel, 0.5+u_mouse.x/u_resolution.x);
	color.g = pattern(st, vel, 0.5+u_mouse.x/u_resolution.x);
	color.b = pattern(st-offset, vel, 0.5+u_mouse.x/u_resolution.x);

	color *= step(0.2, fPos.y);

	o_color = vec4(1.0-color, 1.0);
}