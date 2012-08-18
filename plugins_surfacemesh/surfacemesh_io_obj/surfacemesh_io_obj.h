#pragma once
#include "interfaces/SurfaceMeshModelPlugins.h"

class surfacemesh_io_obj : public SurfaceMeshInputOutputPlugin{
    Q_OBJECT
    Q_INTERFACES(InputOutputPlugin)

public:
    QString name() { return "[SurfaceMesh] Wavefront Object (*.obj)"; }
    Model* open(QString path);
    void save(QString /*path*/, SurfaceMeshModel* /*model*/){
        throw StarlabNotImplementedException("surfacemesh_io_obj::save(..)");
    }
};
