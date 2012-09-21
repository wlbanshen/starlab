#pragma once
#include "qglviewer.h"
#include "SurfaceMeshPlugins.h"
#include "SurfaceMeshHelper.h"

#include "arap_dialog.h"
#include "ARAPDeformer.h"
#include "ARAPDeformerHandle.h"

enum ARAP_MODE{CONTROL_FACES, ANCHOR_FACES, DEFORM};
enum ANCHOR_MODE{MANUAL_POINTS, GEODESIC_DISTANCE};

static uint qHash( const Vertex &key ){return qHash(key.idx()); }
static uint qHash( const Face &key ){return qHash(key.idx()); }

class surfacemesh_mode_arapdeform : public SurfaceMeshModePlugin{
    Q_OBJECT
    Q_INTERFACES(ModePlugin)

public:
    surfacemesh_mode_arapdeform();

    QIcon icon(){ return QIcon(":/surfacemesh_mode_arapdeform.png"); }

    /// Functions part of the EditPlugin system
    void create();
    void destroy(){}

    void postSelection(const QPoint& p);
    void endSelection(const QPoint& p);

    void decorate();
    void drawHandle();
    void drawWithNames();

	void update();

private:
    arap_dialog * dialog;

    ARAP_MODE currentMode;
    ANCHOR_MODE anchorMode;

    Vector3VertexProperty points, src_points;
    Vector3FaceProperty fnormals;

    QSet<Face> controlFaces;
    QSet<Face> anchorFaces;

    QSet<Vertex> controlPoints();

    ARAPDeformer * deformer;
    ARAPDeformerHandle * deform_handle;
    void initDeform();
    int numIterations;

public slots:
    void Deform();

    void setControlMode();
    void setAnchorMode();
    void setDeformMode();
    void setNumIterations(int);
};


