#pragma once 

#include <iostream>
#include <string>
#include <SDL.h>
#include <GL/glew.h>
#include "../../Libs/glm/glm/glm.hpp"

class Exercice {
public:

	GLuint VAO, VBO, shader;
	const char* vertexSource;
	const char* fragmentSource;

	Exercice(const char* vertex, const char* fragment) {
		vertexSource = vertex;
		fragmentSource = fragment;
		//VAO = 0;
		//VBO = 0;
		//shader = 0;
	}
	
	void Initialize() {
		CreateTriangle();
		CompileShaders();
	}

	void Update(float deltaTime) {

	}

	void Render() {

		glUseProgram(shader);

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		glUseProgram(0);
	}

	void CreateTriangle() {
		GLfloat vertices[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f,  -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &VAO);//what data a vertex has
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);// defines the data itself
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// defines where and how vertex shaders can access vertex data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
		GLuint theShader = glCreateShader(shaderType);
		std::cout << "shaderCode:\n" << shaderCode << " ------ " << std::endl;

		const GLchar* theCode[1];
		theCode[0] = shaderCode;

		GLint codeLength[1];
		codeLength[0] = strlen(shaderCode);

		glShaderSource(theShader, 1, theCode, codeLength);
		glCompileShader(theShader);

		GLint result = 0;
		GLchar eLog[1024] = { 0 };

		//glGetProgramiv(theShader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
			const char* shaderName = (shaderType == GL_VERTEX_SHADER) ? "VERTEX SHADER" : "FRAGMENT SHADER";
			printf("Error compiling the %s program: %s\n", shaderName, eLog);
			return;
		}

		glAttachShader(theProgram, theShader);
	}

	void CompileShaders() {
		shader = glCreateProgram();
		if (!shader) {
			printf("Error creating shader program!\n");
			return;
		}

		//std::cout << "vertexSource:\n" << vertexSource << " ------ " << std::endl;
		//std::cout << "fragmentSource:\n" << fragmentSource << " ------ " << std::endl;
		AddShader(shader, vertexSource, GL_VERTEX_SHADER);
		AddShader(shader, fragmentSource, GL_FRAGMENT_SHADER);

		GLint result = 0;
		GLchar eLog[1024] = { 0 };

		// https://stackoverflow.com/questions/31465295/opengl-shader-linking
		//glBindAttribLocation(shader, 0, "pos");

		glLinkProgram(shader);
		glGetProgramiv(shader, GL_LINK_STATUS, &result);

		if (!result) {
			glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
			printf("Error linking program: %s\n", eLog);
			return;
		}

		glValidateProgram(shader);
		glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

		if (!result) {
			glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
			printf("Error validating program: %s\n", eLog);
			return;
		}

	}
};