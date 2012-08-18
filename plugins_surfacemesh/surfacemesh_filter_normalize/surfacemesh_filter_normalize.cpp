#include "surfacemesh_filter_normalize.h"
#include "StarlabDrawArea.h"
#include "SurfaceMeshTypes.h"
using namespace SurfaceMeshTypes;

QString printBounding(QBox3D box){
    QString retval;
    QTextStream sout(&retval);
    QVector3D c = box.center();
    QVector3D s   = box.size();
    sout << "Center[" << c.x() << " " << c.y() << " " << c.z() << "]" 
         << "  Size[" << s.x() << " " << s.y() << " " << s.z() << "]";
    return retval;
}

void surfacemesh_filter_normalize::applyFilter(SurfaceMeshModel *model, RichParameterSet *, StarlabDrawArea *drawArea){
    SurfaceMeshModel* mesh = qobject_cast<SurfaceMeshModel*>(model);
    if(!mesh) throw StarlabException("FAIL");

    qDebug() << "Old bounding box: " << printBounding(mesh->getBoundingBox());
    /// Just to be sure... update it
    mesh->updateBoundingBox();        
    QBox3D bbox = mesh->getBoundingBox();
    
    Vector3 offset = bbox.center();
    
#if 0
    /// Normalize to unit bounding
    Scalar scale = bbox.size().length();
#else
    /// Normalize to have longest side size = 1
    QVector3D s = bbox.size();
    Scalar scale = qMax(s.x(),qMax(s.y(),s.z()));
#endif    
        
    Surface_mesh::Vertex_property<Point> points = mesh->get_vertex_property<Point>("v:point");
    for (Surface_mesh::Vertex_iterator vit = mesh->vertices_begin(); vit != mesh->vertices_end(); ++vit){
        Point& p = points[vit];
        p.x() -= offset.x();
        p.y() -= offset.y();
        p.z() -= offset.z();
        p.x() /= scale;
        p.y() /= scale;
        p.z() /= scale;
    }
    
    /// And update it after, so we can reset the viewpoint
    mesh->updateBoundingBox();
    if(drawArea) drawArea->resetView();
    
    qDebug() << "New bounding box: " << printBounding(mesh->getBoundingBox());
}

Q_EXPORT_PLUGIN(surfacemesh_filter_normalize)


