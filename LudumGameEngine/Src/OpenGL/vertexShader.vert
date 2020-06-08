#version 330

layout(location = 0) in vec3 posicao;

void main() {
	gl_Position = vec4(0.4 * posicao.x, 0.4 * posicao.y, posicao.z, 1.0);
}