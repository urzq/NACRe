#include <assert.h>
#include <memory>
#include <functional>

#define PAR_SHAPES_IMPLEMENTATION
#include <par/par_shapes.h>

#include "Core/Memory.h"

#include "VertexBuffer.h"
#include "VertexBufferData.h"
#include "VertexBufferManager.h"

using namespace memory;

// Create a par_shapes_mesh from a name ("cube", "sphere"), that knows how to delete itself.
static unique_ptr_del<par_shapes_mesh>
CreateParShapeMesh(const std::string& meshName)
{
	auto mesh_delete = [](par_shapes_mesh* m) {
		par_shapes_free_mesh(m);
	};

	if (meshName == "cube")
		return{ par_shapes_create_cube(), mesh_delete };

	if (meshName == "sphere")
		return{ par_shapes_create_subdivided_sphere(5), mesh_delete };

	if (meshName == "dodecahedron")
		return{ par_shapes_create_dodecahedron(), mesh_delete };

	if (meshName == "tetrahedron")
		return{ par_shapes_create_tetrahedron(), mesh_delete };

	if (meshName == "octahedron")
		return{ par_shapes_create_octahedron(), mesh_delete };

	if (meshName == "icosahedron")
		return{ par_shapes_create_icosahedron(), mesh_delete };

	// TODO: maybe do something smarter ?
	assert(false);
	return nullptr;
}

std::shared_ptr<VertexBuffer> VertexBufferManager::GetVertexBuffer(const std::string& meshName)
{
	// If we have copied the weak_ptr (no &), and created a shared ptr from it, we would break the ref count.
	std::weak_ptr<VertexBuffer>& vertexBuffer = m_VertexBufferCache[meshName];

	// if we never created the vertex buffer.
	if (vertexBuffer.expired())
	{
		// The lambda is called when the ref count reaches 0. it removes the vertex buffer from the cache.
		std::shared_ptr<VertexBuffer> sharedVertexBuffer(NewVertexBuffer(meshName), [this, meshName](VertexBuffer* vb) {
			m_VertexBufferCache.erase(meshName);
			delete vb;
		});

		// Make the cache entry point to the newly created vertex buffer.
		vertexBuffer = sharedVertexBuffer;

		return sharedVertexBuffer;
	}
	// Simple case: the vertex buffer is already loaded. Just return it.
	else
	{
		return vertexBuffer.lock();
	}
}

VertexBuffer* VertexBufferManager::NewVertexBuffer(const std::string& meshName)
{
	auto mesh = CreateParShapeMesh(meshName);

	par_shapes_unweld(mesh.get(), true);
	par_shapes_compute_normals(mesh.get());

	VertexBufferData vbd;
	vbd.NbVertices = mesh->npoints;
	vbd.Vertices = mesh->points;
	vbd.Normals = mesh->normals;
	vbd.UV = mesh->tcoords;

	return new VertexBuffer(vbd);
}

std::shared_ptr<VertexBuffer> VertexBufferManager::CreateVertexBuffer(const VertexBufferData& vbd)
{
	return std::make_shared<VertexBuffer>(vbd);
}