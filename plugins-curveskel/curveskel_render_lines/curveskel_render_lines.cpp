#include "curveskel_render_lines.h"
#include <qgl.h>

void curveskel_render_lines::render(){
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
        render_nodes();
        render_edges();
    glEnable(GL_LIGHTING);
}

void curveskel_render_lines::render_nodes(){
//    Vector3VertexProperty vcoord = mesh->get_vertex_property<Vector3>("v:point");
//
//#if 1
//    widget()->qglColor(model()->color);
//    glBegin(GL_POINTS);
//        foreach(Vertex v, mesh->vertices())
//            glVertex3dv(vcoord[v].data());
//    glEnd();
//#else
//    glPointSize(4.0f);
//    glEnable(GL_POINT_SMOOTH);
//    foreach(Vertex v, mesh->vertices()){
//        Vector3 p = vcoord[v];
//        glColor3f(0.9f, 0.2f, 0.2f);
//        glPointSize(7.0f);
//        glBegin(GL_POINTS);
//            glVertex3f(p[0], p[1], p[2]);
//        glEnd();
//
//        // White Border
//        glPointSize(10.0f);
//        glColor3f(1,1,1);
//        glBegin(GL_POINTS);
//            glVertex3f(p[0], p[1], p[2]);
//        glEnd();
//    }
//#endif
}

void curveskel_render_lines::render_edges(){
//    Vector3VertexProperty vcoord = mesh->get_vertex_property<Vector3>("v:point");
//    glPointSize(4.0f);
//    glColor3f(1,0,0);
//    glEnable(GL_POINT_SMOOTH);
//    float oldLineWidth = 0;
//    glGetFloatv(GL_LINE_WIDTH, &oldLineWidth);
//    glLineWidth(1.5f);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBegin(GL_LINES);
//        foreach(Edge e, mesh->edges()){
//            Vertex v0 = mesh->vertex(e,0);
//            Vertex v1 = mesh->vertex(e,1);
//            Vector3 p0 = vcoord[v0];
//            Vector3 p1 = vcoord[v1];
//            glColor3f(1.0f, 0.2f, 0.2f);
//            glVertex3f(p0[0], p0[1], p0[2]);
//            glColor3f(1.0f, 0.2f, 0.2f);
//            glVertex3f(p1[0], p1[1], p1[2]);
//        }
//    glEnd();
//    glDisable(GL_BLEND);
}


Q_EXPORT_PLUGIN(curveskel_render_lines)
