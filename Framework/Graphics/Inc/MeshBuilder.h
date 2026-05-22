#pragma once

#include "MeshTypes.h"

namespace VisualEngine::Graphics
{
	class MeshBuilder
	{
	public:
		// cube
		static MeshP CreateVertexCubePC(float size, const Color& color);
		static MeshPC CreateCubePC(float size);

		static MeshPC CreateBoxPC(float width, float height, float depth);
		static MeshPC CreatePyramidPC(float size);

		static MeshPC CreatePlanePC(int numRows, int numColums, float spacing, bool horizontal = true);

		// cylinder
		static MeshPC CreateCylinderPC(int slices, int rings);

		static MeshPC CreateSpherePC(int slices, int rings, float radius);
	};
}