#ifndef __VERTEX_BUFFER_MANAGER_H__
#define __VERTEX_BUFFER_MANAGER_H__

#include <string>
#include <memory>
#include <unordered_map>

#include <glad/glad.h>


class VertexBuffer;
struct VertexBufferData;

class VertexBufferManager
{
public:
	// Returns a cached standard mesh by name (cube, sphere etc...).
	// /!\ Be extra cautious if one day we clean m_VertexBuffer. Other objets can still have references on a VertexBuffer, and it won't be destroyed properly.
	std::shared_ptr<VertexBuffer> GetVertexBuffer(const std::string& meshName);

	// Creates a VertexBuffer from a VertexBufferData. 
	std::shared_ptr<VertexBuffer> CreateVertexBuffer(const VertexBufferData& vbd);

private:
	VertexBuffer* NewVertexBuffer(const std::string& meshName);

private:
	std::unordered_map<std::string, std::weak_ptr<VertexBuffer>> m_VertexBufferCache;
};

#endif