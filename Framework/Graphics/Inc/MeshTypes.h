#pragma once

#include "VertexTypes.h"

namespace VisualEngine::Graphics
{
	template<class VertexT>
	struct MeshBase
	{
		using Vertextype = VertexT;
		std::vector<VertexT> vertices;
		std::vector<uint32_t> indices;
	};

	using MeshP = MeshBase<VertexP>;
	using MeshPC = MeshBase<VertexPC>;
	using MeshPX = MeshBase<VertexPX>;
	using Mesh = MeshBase<Vertex>;
}