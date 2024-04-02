#pragma once

#include "Surface.hpp"
#include "datatypes/Lighting.hpp"
#include "datatypes/Dnum.hpp"
#include "gl/GpuProgram.hpp"

class Function : public Surface {

private:
	std::string positionFormula;
	std::string normalFormula;

public:
	Function();
	Function(unsigned int N, unsigned int M);
	inline void setPositionFormula(const char* formula) { positionFormula = std::string(formula); }
	inline void setNormalFormula(const char* formula) { normalFormula = std::string(formula); }

	void eval(float u, float v, glm::vec3& pos, glm::vec3& norm) override;

private:
	void trimBrackets(std::string& formula);
	bool isOperation(std::string operation, std::string formula);
	bool isNumber(const std::string& formula);
	float toNumber(const std::string& formula);
	std::string trimOperation(std::string& operation);
	void removeSpaces(std::string& formula);
	std::string leftOperand(unsigned int index, std::string operation);
	std::string rightOperand(unsigned int index, std::string operation);

	Dnum evaluateFormula(Dnum x, Dnum y, std::string formula);
	
};