#include "VertexBufferData.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(VertexBufferData& data)
{
	m_NbVertices = data.NbVertices;
	int index = 0;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	if (data.Vertices)
	{
		glGenBuffers(1, &m_VBO_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_vertices);
		glBufferData(GL_ARRAY_BUFFER, data.NbVertices * sizeof(float) * 3, data.Vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(index);
		index++;
	}

	if (data.Normals)
	{
		glGenBuffers(1, &m_VBO_normals);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_normals);
		glBufferData(GL_ARRAY_BUFFER, data.NbVertices * sizeof(float) * 3, data.Normals, GL_STATIC_DRAW);
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(index);
		index++;
	}
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_VBO_vertices);
	glDeleteBuffers(1, &m_VBO_normals);

	glDeleteVertexArrays(1, &m_VAO);
}

int VertexBuffer::GetNbVertice() const
{
	return m_NbVertices;
}

void VertexBuffer::Use() const
{
	glBindVertexArray(m_VAO);
}