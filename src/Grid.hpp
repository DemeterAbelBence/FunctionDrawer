#include "Object.hpp"

class Grid : public Object{

private:
	unsigned int N = 6;
	unsigned int numberOfPoints = 0;
	float scale;

public:
	Grid();
	Grid(unsigned int _N);
	inline void setScale(float value) { scale = value; }
	void create() override;
	void draw() const override;
};