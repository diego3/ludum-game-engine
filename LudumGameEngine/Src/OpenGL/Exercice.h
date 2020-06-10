#pragma once 

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <SDL.h>
#include <GL/glew.h>
#include "../../Libs/glm/glm/glm.hpp"
#include "../../Libs/glm/glm/gtc/matrix_transform.hpp"
#include "../../Libs/glm/glm/gtc/type_ptr.hpp"

class Exercice {
public:

	const float toRadians = 3.14159265f / 180.0f;

	GLuint VAO, VBO, IBO, shader, 
		uniformModel, 
		uniformProjection;

	const char* vertexSource;
	const char* fragmentSource;
	GLfloat aspectRatio;

	bool direction = true;
	float triOffset = 0.0f;
	float triMaxOffset = 0.6f;
	float triIncrement = 1.0f;

	float rotControl = 0.0f;
	float rotMaxDegree = 360.f;

	// for debug only
	bool printShaderSource = false;

	glm::mat4 projection;

	Exercice(const char* vertex, const char* fragment, GLfloat aspect) {
		vertexSource = vertex;
		fragmentSource = fragment;
		VAO = 0;
		VBO = 0;
		shader = 0;
		uniformModel = 0;
		IBO = 0;
		aspectRatio = aspect;
		projection = glm::mat4(1.0f);
	}
	
	void Initialize() {
		CreateTriangle();
		CompileShaders();

		projection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
	}

	void Update(float deltaTime) {
		//glm::mat4 model(1.0f);
		rotControl += 1.0f;
		if (rotControl >= rotMaxDegree) {
			rotControl = 0.0f;
		}


		if (direction) {
			triOffset += triIncrement * deltaTime;
		}
		else {
			triOffset -= triIncrement * deltaTime;
		}

		if (abs(triOffset) >= triMaxOffset) {
			direction = !direction;
		}
	}

	void Render() {
		glUseProgram(shader);

		glm::mat4 model(1.0f);
		
		model = glm::translate(model, glm::vec3(0.0f, triOffset , -2.5f));
		model = glm::rotate(model, glm::radians(rotControl), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	void CreateTriangle() {
		unsigned int indices[] = {
			0, 3, 1,
			1, 3, 2,
			2, 3, 0,
			0, 1, 2
		};

		GLfloat vertices[] = {
			-1.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 1.0f,
			1.0f,  -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &VAO);//what data a vertex has
		glBindVertexArray(VAO);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		glGenBuffers(1, &VBO);// defines the data itself
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// defines where and how vertex shaders can access vertex data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// IBO always AFTER VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
		GLuint theShader = glCreateShader(shaderType);
		if (printShaderSource) {
			std::cout << "shaderCode:\n" << shaderCode << " ------ " << std::endl;
		}

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

		uniformModel = glGetUniformLocation(shader, "model");
		uniformProjection = glGetUniformLocation(shader, "projection");
	}
};