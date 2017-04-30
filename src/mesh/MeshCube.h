#ifndef __MESH_CUBE_H__
#define __MESH_CUBE_H__

#include <GL/glew.h>
#include <glfw3.h>

class MeshCube
{
public:
	MeshCube();
	~MeshCube();

	void Use();
	void Disable();

private:
	GLuint m_VertexArrayObject;
	GLuint m_VertexBufferObject;
};

#endif