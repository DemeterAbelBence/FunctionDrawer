#pragma once

#include "Lighting.hpp"

Lighting::LightSource::LightSource() {}

Lighting::LightSource::LightSource(glm::vec3 _position, glm::vec3 _diffuse, glm::vec3 _ambient) {
	position = _position;
	diffuse = _diffuse;
	ambient = _ambient;
}

Lighting::Material::Material() {}

Lighting::Material::Material(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess) {
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
}
