#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

#include <GL/glew.h>

struct VertexBufferData;

class VertexBuffer
{
	friend class VertexBufferManager;

public:
	int GetNbVertice() const;
	void Use() const;

private:
	VertexBuffer(VertexBufferData& data);
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer& operator=(const VertexBuffer& other) = delete;
	VertexBuffer(VertexBuffer&& other) = delete;
	VertexBuffer& operator=(VertexBuffer&& other) = delete;

	~VertexBuffer();

private:
	GLuint m_VAO;

	GLuint m_VBO_position;
	GLuint m_VBO_normals;

	int m_NbVertices;
};

#endif