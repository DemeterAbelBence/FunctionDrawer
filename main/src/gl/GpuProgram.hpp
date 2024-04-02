#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GLEW/glew.h>
#include <glm.hpp>

class GpuProgram {

private:
	unsigned int programId;
	std::string vertexSource;
	std::string fragmentSource;

	void displayShaderCompilationResult(unsigned int type, unsigned int id);
	unsigned int compileShader(unsigned int type, const std::string& source);

public:

	GpuProgram();
	GpuProgram(const std::string& _vertexSource, const std::string& _fragmentSource);
	void setVertexShaderSource(const std::string& _vertexSource) { vertexSource = _vertexSource; }
	void setFragmentShaderSource(const std::string& _fragmentSource) { fragmentSource = _fragmentSource; }
	unsigned int getProgramId() { return programId; }

	void createProgram();
	void readVertexSource(const std::string& filePath);
	void readFragmentSource(const std::string& filePath);
	inline void bind() const { glUseProgram(programId); }
	inline void unBind() const { glUseProgram(0); }

	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void setFloat(const std::string& name, float value) const;
};


