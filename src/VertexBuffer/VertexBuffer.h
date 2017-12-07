#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

#include <GL/glew.h>

struct VertexBufferData;

class VertexBuffer
{
public:
	VertexBuffer(const VertexBufferData& data);
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer& operator=(const VertexBuffer& other) = delete;
	VertexBuffer(VertexBuffer&& other) = delete;
	VertexBuffer& operator=(VertexBuffer&& other) = delete;

	~VertexBuffer();

	int GetNbVertice() const;
	void Use() const;

private:
	GLuint m_VAO = -1;

	GLuint m_VBO_vertices = -1;
	GLuint m_VBO_normals = -1;
	GLuint m_VBO_UV = -1;


	int m_NbVertices;
};

#endif