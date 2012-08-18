#pragma once
#include <string>
#include "WingedgeMesh.h"
#include "./Vector.h"

namespace CurveskelTypes{
/// @{ Basic types
    typedef SkelVector<double,3> Vector3;
	typedef Vector3 Point;
    typedef double Scalar;
    typedef std::string String;
/// @}

/// @{ Default property names
    const String VCOORD = "v:point";
/// @}

/// @{ WidgedgeMesh typeps
    typedef WingedgeMesh<Scalar,Vector3> MyWingedMesh;
    typedef MyWingedMesh::Vertex Vertex;
    typedef MyWingedMesh::Edge   Edge;
    typedef MyWingedMesh::Vertex_property<Vector3> Vector3VertexProperty;    
/// @}
}
