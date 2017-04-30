#ifndef __MESH_LIGHT_H__
#define __MESH_LIGHT_H__

#include <GL/glew.h>
#include <glfw3.h>

class MeshLight
{
public:
	MeshLight();
	~MeshLight();

	void Use();
	void Disable();

private:
	GLuint m_VertexArrayID;
	GLuint m_Vertexbuffer;
};

#endif