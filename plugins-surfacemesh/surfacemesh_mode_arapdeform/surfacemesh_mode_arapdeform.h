#pragma once
#include "qglviewer.h"
#include "SurfaceMeshPlugins.h"
#include "SurfaceMeshHelper.h"

enum DrawElementType{VERT_IDX, FACE_IDX, EDGE_IDX, HDGE_IDX};

class surfacemesh_mode_arapdeform : public SurfaceMeshModePlugin{
    Q_OBJECT
    Q_INTERFACES(ModePlugin)

    QIcon icon(){ return QIcon(":/surfacemesh_mode_arapdeform.png"); }

    /// Functions part of the EditPlugin system
    void create();
    void destroy(){}

	void update();
};
