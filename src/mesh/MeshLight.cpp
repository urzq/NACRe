#include <GL/glew.h>

#include "MeshLight.h"

MeshLight::MeshLight()
{
	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-0.2f,-0.2f,-0.2f,
		-0.2f,-0.2f, 0.2f,
		-0.2f, 0.2f, 0.2f,
		0.2f, 0.2f,-0.2f,
		-0.2f,-0.2f,-0.2f,
		-0.2f, 0.2f,-0.2f,
		0.2f,-0.2f, 0.2f,
		-0.2f,-0.2f,-0.2f,
		0.2f,-0.2f,-0.2f,
		0.2f, 0.2f,-0.2f,
		0.2f,-0.2f,-0.2f,
		-0.2f,-0.2f,-0.2f,
		-0.2f,-0.2f,-0.2f,
		-0.2f, 0.2f, 0.2f,
		-0.2f, 0.2f,-0.2f,
		0.2f,-0.2f, 0.2f,
		-0.2f,-0.2f, 0.2f,
		-0.2f,-0.2f,-0.2f,
		-0.2f, 0.2f, 0.2f,
		-0.2f,-0.2f, 0.2f,
		0.2f,-0.2f, 0.2f,
		0.2f, 0.2f, 0.2f,
		0.2f,-0.2f,-0.2f,
		0.2f, 0.2f,-0.2f,
		0.2f,-0.2f,-0.2f,
		0.2f, 0.2f, 0.2f,
		0.2f,-0.2f, 0.2f,
		0.2f, 0.2f, 0.2f,
		0.2f, 0.2f,-0.2f,
		-0.2f, 0.2f,-0.2f,
		0.2f, 0.2f, 0.2f,
		-0.2f, 0.2f,-0.2f,
		-0.2f, 0.2f, 0.2f,
		0.2f, 0.2f, 0.2f,
		-0.2f, 0.2f, 0.2f,
		0.2f,-0.2f, 0.2f
	};

	glGenBuffers(1, &m_Vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

MeshLight::~MeshLight()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &m_Vertexbuffer);
	glDeleteVertexArrays(1, &m_VertexArrayID);
}

void MeshLight::Use()
{
	glBindVertexArray(m_VertexArrayID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
}

void MeshLight::Disable()
{
	glDisableVertexAttribArray(0);
}