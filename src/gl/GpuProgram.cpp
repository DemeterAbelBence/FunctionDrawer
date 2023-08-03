#pragma once

#include "GpuProgram.hpp"

void GpuProgram::displayShaderCompilationResult(unsigned int type, unsigned int id) {
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader!!!" << std::endl;

		std::cout << message << std::endl;
		delete[] message;
	}
	else if (result == GL_TRUE) {
		std::cout << "Successful " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader compilation!" << std::endl;
	}
}

unsigned int GpuProgram::compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	displayShaderCompilationResult(type, id);

	return id;
}

GpuProgram::GpuProgram() : programId(0) {}

GpuProgram::GpuProgram(const std::string& _vertexSource, const std::string& _fragmentSource) {
	vertexSource = _vertexSource;
	fragmentSource = _fragmentSource;

	createProgram();
}

void GpuProgram::createProgram() {
	unsigned int id = glCreateProgram();
	unsigned int vertexId = compileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragmentId = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	glAttachShader(id, vertexId);
	glAttachShader(id, fragmentId);
	glLinkProgram(id);
	glValidateProgram(id);

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);

	programId = id;
}

void GpuProgram::readVertexSource(const std::string& filePath) {
	std::ifstream stream(filePath);
	std::string line;

	while (getline(stream, line)) {
		vertexSource += line;
		vertexSource += '\n';
	}
}

void GpuProgram::readFragmentSource(const std::string& filePath) {
	std::ifstream stream(filePath);
	std::string line;

	while (getline(stream, line)) {
		fragmentSource += line;
		fragmentSource += '\n';
	}
}

void GpuProgram::setVec3(const std::string& name, glm::vec3 value) const {
	glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void GpuProgram::setVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(programId, name.c_str()), x, y, z);
}

void GpuProgram::setMat4(const std::string& name, glm::mat4 mat) const {
	glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GpuProgram::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}