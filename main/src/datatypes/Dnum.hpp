#pragma once

#include <glm.hpp>

struct Dnum {
	float val; //value
	glm::vec3 der; //derivative

	Dnum(float _val, glm::vec3 _der = glm::vec3(0)) { val = _val, der = _der; }
	Dnum operator+(Dnum r);
	Dnum operator*(Dnum r);
	Dnum operator/(Dnum r);
};

Dnum _Sin(Dnum r);
Dnum _Cos(Dnum r);
Dnum _Log(Dnum r);
Dnum _Exp(Dnum r);
