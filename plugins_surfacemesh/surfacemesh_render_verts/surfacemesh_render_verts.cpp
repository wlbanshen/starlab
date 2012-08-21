#include <qgl.h>
#include "surfacemesh_render_verts.h"
#include "SurfaceMeshHelper.h"

void surfacemesh_render_verts::render(){
    Surface_mesh::Vertex_property<Point> points = mesh()->vertex_property<Point>("v:point");
	glBegin(GL_POINTS);
    glDisable(GL_LIGHTING);
    glPointSize(3.0);
        foreach(Vertex v, mesh()->vertices())
            glVertex3dv(points[v].data());
	glEnd();
}

Q_EXPORT_PLUGIN(surfacemesh_render_verts)
