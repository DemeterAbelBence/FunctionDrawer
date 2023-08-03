#include "Object.hpp"

class Grid : public Object{

private:
	static const unsigned int N = 6;
	unsigned int numberOfPoints = 0;
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	float scale;

public:
	Grid();
	inline void setCenter(glm::vec3 value) { center = value; }
	inline void setScale(float value) { scale = value; }
	void create() override;
	void draw() const override;
};