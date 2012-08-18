#include "surfacemesh_io_obj.h"
#include "Document.h"

Model* surfacemesh_io_obj::open(QString path){
    SurfaceMeshModel* model = new SurfaceMeshModel(path);
    /// Load the mesh
    model->read(qPrintable(path));
    return model;
}

Q_EXPORT_PLUGIN(surfacemesh_io_obj)

