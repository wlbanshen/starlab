#include "CurveskelModel.h"
#include "CurveskelQForEach.h"
#include "StarlabException.h"

using namespace std;
using namespace CurveskelTypes;

CurveskelModel::CurveskelModel(QString path, QString name) : Model(path,name){}

void CurveskelModel::updateBoundingBox(){
    Vector3VertexProperty vcoord = get_vertex_property<Vector3>(VCOORD);
    _bbox.setToNull();
    foreach(Vertex v, this->vertices())
        _bbox.unite( vcoord[v] );
}

SkeletonForEachEdgeHelper CurveskelModel::edges(){ 
    return SkeletonForEachEdgeHelper(this); 
}
SkeletonForEachVertexHelper CurveskelModel::vertices(){ 
    return SkeletonForEachVertexHelper(this); 
}

//Explicit Template Instantiation
template class WingedgeMesh <double, CurveskelTypes::SkelVector<double,3> >;
