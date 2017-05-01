#ifndef __COLOR_H_
#define __COLOR_H_

#include <glm/glm.hpp>

class Color
{
public:
	Color(int hexa);

	operator glm::vec3();

	float r;
	float g;
	float b;
};

#endif