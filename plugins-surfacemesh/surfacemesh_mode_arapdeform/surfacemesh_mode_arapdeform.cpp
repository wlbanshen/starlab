#include <QMouseEvent>
#include "surfacemesh_mode_arapdeform.h"
#include "StarlabDrawArea.h"

surfacemesh_mode_arapdeform::surfacemesh_mode_arapdeform()
{
    dialog = new arap_dialog(this);

    this->deformer = NULL;
    this->deform_handle = NULL;
}

void surfacemesh_mode_arapdeform::create()
{
    dialog->show();

    this->currentMode = CONTROL_FACES;
    this->anchorMode = MANUAL_POINTS;
    this->numIterations = 1;

    update();
}

void surfacemesh_mode_arapdeform::postSelection(const QPoint &p)
{
    Q_UNUSED(p);

    int selectedId = drawArea()->selectedName();
    if(selectedId < 0) return;

    Face f(selectedId);

    switch(currentMode)
    {
        case CONTROL_FACES: controlFaces.insert(f); break;
        case ANCHOR_FACES: anchorFaces.insert(f); break;
    }
}

void surfacemesh_mode_arapdeform::endSelection( const QPoint& p )
{
    drawArea()->defaultEndSelection(p);
}

void surfacemesh_mode_arapdeform::decorate()
{
    glColor3d(1,1,1);

    switch(currentMode)
    {
        case CONTROL_FACES:
            drawArea()->drawText(50, 50, "Mode: Control points"); break;
        case ANCHOR_FACES:
            drawArea()->drawText(50, 50, "Mode: Anchor points"); break;
        case DEFORM:
        {
            drawArea()->drawText(50, 50, "Mode: Deform!");
            drawHandle();
            break;
        }
    }

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-10, 10);

    // Control faces
    foreach(Face f, controlFaces){
        glColor3d(0,1,0);

        glBegin(GL_POLYGON);
        glNormal3dv(fnormals[f]);
        Surface_mesh::Vertex_around_face_circulator vit, vend;
        vit = vend = mesh()->vertices(f);
        do{ glVertex3dv(points[vit]); } while(++vit != vend);
        glEnd();
    }

    // Anchor faces
    foreach(Face f, anchorFaces){
        glColor3d(1,0,0);

        glBegin(GL_POLYGON);
        glNormal3dv(fnormals[f]);
        Surface_mesh::Vertex_around_face_circulator vit, vend;
        vit = vend = mesh()->vertices(f);
        do{ glVertex3dv(points[vit]); } while(++vit != vend);
        glEnd();
    }

    glDisable(GL_POLYGON_OFFSET_FILL);
}

void surfacemesh_mode_arapdeform::drawHandle()
{
    if(!deform_handle) return;

    int pixels = 32;
    double scaling = pixels * drawArea()->camera()->pixelGLRatio(Vec(0,0,0));

    glPushMatrix();
    glMultMatrixd(deform_handle->matrix());

    glDisable(GL_LIGHTING);
    glLineWidth(4.0f);

    glBegin(GL_LINES);

    glColor3d(1,0,0);
    glVertex3fv(Vec(0,0,0));
    glVertex3fv(Vec(1,0,0) * scaling);

    glColor3d(0,1,0);
    glVertex3fv(Vec(0,0,0));
    glVertex3fv(Vec(0,1,0) * scaling);

    glColor3d(0,0,1);
    glVertex3fv(Vec(0,0,0));
    glVertex3fv(Vec(0,0,1) * scaling);

    glEnd();
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

void surfacemesh_mode_arapdeform::drawWithNames()
{
    foreach(Face f, mesh()->faces())
    {
        glPushName(f.idx());
        glBegin(GL_POLYGON);
        Surface_mesh::Vertex_around_face_circulator vit, vend;
        vit = vend = mesh()->vertices(f);
        do{ glVertex3dv(points[vit]); } while(++vit != vend);
        glEnd();
        glPopName();
    }
}

void surfacemesh_mode_arapdeform::update()
{
    points = mesh()->vertex_property<Vector3>(VPOINT);
    fnormals = mesh()->face_property<Vector3>(FNORMAL);

    src_points = mesh()->vertex_property<Vector3>("v:src_points");
    foreach(Vertex v, mesh()->vertices()) src_points[v] = points[v];
}

QSet<Vertex> surfacemesh_mode_arapdeform::controlPoints()
{
    QSet<Vertex> cpoints;

    foreach(Face f, controlFaces){
        Surface_mesh::Vertex_around_face_circulator vit, vend;
        vit = vend = mesh()->vertices(f);
        do{ cpoints.insert(vit); }
        while(++vit != vend);
    }

    return cpoints;
}

void surfacemesh_mode_arapdeform::initDeform()
{
    // Check if everything is set and ready
    if(!controlFaces.size() || !anchorFaces.size()){
        setControlMode();
        drawArea()->displayMessage("Please add both control and anchor regions.");
        drawArea()->updateGL();
        return;
    }

    // Create new As-rigid-as-possible deformer
    deformer = new ARAPDeformer(mesh());
    Vector3 handleCenter(0);
    QSet<Vertex> cpoints = controlPoints();

    // Set anchor points
    foreach(Face f, anchorFaces)
    {
        Surface_mesh::Vertex_around_face_circulator vit, vend;
        vit = vend = mesh()->vertices(f);
        do{ deformer->SetAnchor(vit); }
        while(++vit != vend);
    }

    // Set control points and find handle center
    foreach(Vertex v, cpoints){
        deformer->UpdateControl(v, points[v]);
        handleCenter += points[v];
    }
    handleCenter /= cpoints.size();

    // setup deformation handle
    deform_handle = new ARAPDeformerHandle( handleCenter );
    drawArea()->setManipulatedFrame( deform_handle );
    this->connect(deform_handle, SIGNAL(manipulated()), SLOT(Deform()));
}

void surfacemesh_mode_arapdeform::Deform()
{
    // Update control positions
    foreach(Vertex v, controlPoints())
        points[v] = deform_handle->transform( src_points[v] );

    deformer->Deform( numIterations );

    mesh()->update_face_normals();
    mesh()->update_vertex_normals();
}

void surfacemesh_mode_arapdeform::setControlMode(){ currentMode = CONTROL_FACES; drawArea()->updateGL(); }
void surfacemesh_mode_arapdeform::setAnchorMode(){ currentMode = ANCHOR_FACES; drawArea()->updateGL(); }
void surfacemesh_mode_arapdeform::setDeformMode(){ currentMode = DEFORM; initDeform(); drawArea()->updateGL(); }
void surfacemesh_mode_arapdeform::setNumIterations(int iters){ this->numIterations = iters; }

Q_EXPORT_PLUGIN(surfacemesh_mode_arapdeform)
