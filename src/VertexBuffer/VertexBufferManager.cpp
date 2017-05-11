#include <assert.h>
#include <memory>
#include <functional>

#define PAR_SHAPES_IMPLEMENTATION
#include <grasshoper/par_shapes.h>

#include "VertexBuffer.h"
#include "VertexBufferData.h"
#include "VertexBufferManager.h"

VertexBufferManager::VertexBufferManager()
{
}

VertexBufferManager::~VertexBufferManager()
{
	for (auto& entry : m_VertexBuffers)
	{
		delete entry.second;
	}
}

VertexBuffer* VertexBufferManager::GetVertexBuffer(const std::string& meshName)
{
	auto lower_bound = m_VertexBuffers.lower_bound(meshName);

	if (lower_bound != m_VertexBuffers.end() && !(m_VertexBuffers.key_comp()(meshName, lower_bound->first)))
	{
		return lower_bound->second;
	}
	else
	{
		VertexBuffer* vertexBuffer = CreateVertexBuffer(meshName);
		m_VertexBuffers.insert(lower_bound, {meshName, vertexBuffer});    
		return vertexBuffer;
	}
}

std::unique_ptr<par_shapes_mesh, std::function<void(par_shapes_mesh*)>> 
MakeUniqueMesh(par_shapes_mesh* mesh)
{
	auto mesh_delete = [](par_shapes_mesh* m) { 
		par_shapes_free_mesh(m); 
	};

	return { mesh, mesh_delete };
}

VertexBuffer* VertexBufferManager::CreateVertexBuffer(const std::string& meshName)
{
	if (meshName == "cube")
	{
		auto cube = MakeUniqueMesh( par_shapes_create_cube() );
		return CreateVertexBuffer(cube.get());
	}
	else if (meshName == "sphere")
	{
		auto sphere = MakeUniqueMesh(par_shapes_create_subdivided_sphere(5) );
		return CreateVertexBuffer(sphere.get());
	}

	assert(false);
	return nullptr;
}

VertexBuffer* VertexBufferManager::CreateVertexBuffer(par_shapes_mesh* mesh)
{
	par_shapes_unweld(mesh, true);
	par_shapes_compute_normals(mesh);

	VertexBufferData vbd;
	vbd.NbVertices = mesh->npoints;
	vbd.Vertices = mesh->points;
	vbd.Normals = mesh->normals;
	vbd.TextureCoords = mesh->tcoords;

	return new VertexBuffer(vbd);
}