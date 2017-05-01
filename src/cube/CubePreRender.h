#ifndef __CUBE_PRE_RENDER_H__
#define __CUBE_PRE_RENDER_H__

class Program;

class CubePreRender
{
public:
	CubePreRender(const Program& program);

	// Before looping over all the cubes, call this function. It sets the light data in the shader.
	void PreRender(const glm::vec3& lightPos, const glm::vec3& lighColor);

private:
	GLuint m_LightColor;
	GLuint m_LightPos;
};

#endif