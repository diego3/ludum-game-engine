#version 330

layout(location = 0) in vec3 posicao;

uniform mat4 model;

void main() {
	gl_Position = model * vec4(posicao, 1.0);
}