#version 330

layout(location = 0) in vec3 posicao;

out vec4 vColor;

uniform mat4 model;
uniform mat4 projection;

void main() {
	gl_Position = projection * model * vec4(posicao, 1.0);
	vColor = vec4(clamp(posicao, 0.0, 1.0), 1.0);
}