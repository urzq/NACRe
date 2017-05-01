#include "Color.h"

Color::Color(int hexa)
{
	r = ((hexa >> 16) & 0xFF) / 255.0f;
	g = ((hexa >> 8) & 0xFF) / 255.0f;
	b = (hexa & 0xFF) / 255.0f;
}

Color::operator glm::vec3()
{
	return { r, g, b };
}