#pragma once

#include <iostream>
#include "glm.hpp"

namespace Lighting {
	struct LightSource {
		glm::vec3 position;
		glm::vec3 diffuse;
		glm::vec3 ambient;

		LightSource();
		LightSource(glm::vec3 _position, glm::vec3 _diffuse, glm::vec3 _ambient);
	};

	struct Material {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;

		Material();
		Material(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 specular, float _shininess);
	};
}