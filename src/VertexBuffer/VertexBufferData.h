#ifndef __VERTEX_BUFFER_DATA_H__
#define __VERTEX_BUFFER_DATA_H__

struct VertexBufferData
{
	int		NbVertices		= 0;	   // Number of points
	float*	Vertices		= nullptr; // Flat list of 3-tuples (X Y Z X Y Z...)
	float*	Normals			= nullptr; // Optional list of 3-tuples (X Y Z X Y Z...)
	float*	UV	= nullptr; // Optional list of 2-tuples (U V U V U V...)
};

#endif