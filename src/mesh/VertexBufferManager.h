#ifndef __VERTEX_BUFFER_MANAGER_H__
#define __VERTEX_BUFFER_MANAGER_H__

#include <GL/glew.h>
#include <unordered_map>
#include <string>

#include "par_shapes.h"

class VertexBuffer;

class VertexBufferManager
{
public:
	VertexBufferManager();
	VertexBufferManager(const VertexBufferManager& other) = delete;
	VertexBufferManager& operator=(const VertexBufferManager& other) = delete;
	VertexBufferManager(VertexBufferManager&& other) = delete;
	VertexBufferManager& operator=(VertexBufferManager&& other) = delete;
	~VertexBufferManager();

	VertexBuffer* GetVertexBuffer(const std::string& meshName);

private:
	VertexBuffer* CreateVertexBuffer(const std::string& meshName);
	VertexBuffer* CreateVertexBuffer(par_shapes_mesh* mesh);

private:
	std::unordered_map<std::string, VertexBuffer*> m_VertexBuffers;
};

#endif