
#include <QDebug>
#include <QAction>
#include <QtOpenGL>
#include "surface_mesh/gl_wrappers.h"
#include "qgl.h"

#include "SurfaceMeshModel.h"
#include "SurfaceMeshRenderer.h"
#include "SurfaceMeshHelper.h"

using namespace SurfaceMeshTypes;

SurfaceMeshRenderer::SurfaceMeshRenderer() {
	/// Define actions
	_modes->addAction( _mode_cloud             = new QAction(QIcon(":/images/points.png"),    "Points",_modes));
	_modes->addAction( _mode_flatshaded        = new QAction(QIcon(":/images/flat.png"),      "Flat",_modes));
	_modes->addAction( _mode_smoothshaded      = new QAction(QIcon(":/images/smooth.png"),    "Smooth",_modes));
	_modes->addAction( _mode_wireframe         = new QAction(QIcon(":/images/wire.png"),      "Wireframe",_modes));
	_modes->addAction( _mode_flatwire          = new QAction(QIcon(":/images/flatlines.png"), "Flat Wire",_modes));
	_modes->addAction( _mode_transp_smooth     = new QAction(QIcon(":/images/transp_smooth.png"), "Transparent",_modes));

	isReady = false;
}

void SurfaceMeshRenderer::setup(Model *model, QGLWidget *widget, QAction *shader){
	// qDebug() << "SurfaceMeshRenderer::setup()";
	ModelRenderer::setup(model,widget,shader);
	mesh = qobject_cast<SurfaceMeshModel*>(model);
	if(!mesh) throw StarlabException("Unsuitable Model");
	/// Hardcoded default
	_mode_smoothshaded->setChecked(true);
}

void SurfaceMeshRenderer::render(){
	// qDebug() << "SurfaceMeshRenderer::render()";

	if(!isReady) return;

	/// Call the parent renderer to see if he knows what he's doing
	ModelRenderer::render();

	/// Apply global model color
	widget()->qglColor(model()->color);

	QAction* activeMode = renderModes()->checkedAction();
	if(activeMode == _mode_cloud){
		draw_points();
	} else if(activeMode == _mode_flatshaded){
		draw_flat();
	} else if(activeMode == _mode_smoothshaded){
		draw_smooth();
	} else if(activeMode == _mode_wireframe){
		draw_wireframe(); 
	} else if(activeMode == _mode_flatwire){
		draw_flatwire();            
	} else if(activeMode == _mode_transp_smooth){
		draw_transp_smooth();            
	}
}

void SurfaceMeshRenderer::init(){
	ModelRenderer::init();

	QAction* activeMode = renderModes()->checkedAction();
	// re-compute face and vertex normals
	if(activeMode == _mode_flatshaded || activeMode == _mode_smoothshaded || activeMode == _mode_flatwire)
		mesh->update_face_normals();

	if(activeMode == _mode_smoothshaded )
		mesh->update_vertex_normals();

	// update edge indices for OpenGL rendering
	if(activeMode == _mode_wireframe || activeMode == _mode_flatwire){
		edges.clear();
		edges.reserve(mesh->n_edges());
		Surface_mesh::Edge_iterator eit, eend=mesh->edges_end();
		for (eit=mesh->edges_begin(); eit!=eend; ++eit){
			edges.push_back(mesh->vertex(eit, 0).idx());
			edges.push_back(mesh->vertex(eit, 1).idx());
		}
	}

	// update face indices for OpenGL rendering
	if(activeMode == _mode_flatshaded || activeMode == _mode_smoothshaded || activeMode == _mode_flatwire ){
		triangles.clear();
		Surface_mesh::Face_iterator fit, fend=mesh->faces_end();
		Surface_mesh::Vertex_around_face_circulator fvit, fvend;
		Surface_mesh::Vertex v0, v1, v2;
		for (fit=mesh->faces_begin(); fit!=fend; ++fit){
			fvit = fvend = mesh->vertices(fit);
			v0 = fvit;
			v2 = ++fvit;
			do 
			{
				v1 = v2;
				v2 = fvit;
				triangles.push_back(v0.idx());
				triangles.push_back(v1.idx());
				triangles.push_back(v2.idx());
			} 
			while (++fvit != fvend);
		}
	}

	/// Why were we doing this???????
#if 0
	// update color
	Surface_mesh::Vertex_property<Color>  vcolors  = mesh->vertex_property<Color>("v:color");
	Surface_mesh::Vertex_iterator vit, vend = mesh->vertices_end();
	for (vit = mesh->vertices_begin(); vit != vend; ++vit)
		vcolors[vit] = Color(mesh->color);
#endif

	isReady = true;
}

void SurfaceMeshRenderer::draw_points(){
	Surface_mesh::Vertex_property<Point>  points   = mesh->vertex_property<Point>("v:point");
	Surface_mesh::Vertex_property<Point>  vnormals = mesh->vertex_property<Point>("v:normal");
	Surface_mesh::Vertex_property<Scalar> vtex     = mesh->vertex_property<Scalar>("v:tex1D", 0.0);

	// Deal with color
	bool has_vertex_color = mesh->has_vertex_property<Color>("v:color");
	Surface_mesh::Vertex_property<Color>  vcolor;
	if (has_vertex_color) vcolor = mesh->get_vertex_property<Color>("v:color");


#if 0
	// setup vertex arrays
	gl::glVertexPointer(points.data());
	gl::glNormalPointer(vnormals.data());
	gl::glColorPointer(vcolors.data());
	gl::glTexCoordPointer(vtex.data());

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.0, 0.0);
	glDrawArrays(GL_POINTS, 0, mesh->n_vertices());
	glDisableClientState(GL_VERTEX_ARRAY);
#else
	glBegin(GL_POINTS);
	// glPointSize(1.0);
	foreach(Surface_mesh::Vertex v, mesh->vertices())
		glVertex3dv(points[v].data());
	glEnd();
#endif    
}

void SurfaceMeshRenderer::draw_smooth(){

	Surface_mesh::Vertex_property<Point>  points = mesh->vertex_property<Point>("v:point");    
	Surface_mesh::Vertex_property<Point>  vnormals = mesh->vertex_property<Point>("v:normal");

	// Deal with color
	bool has_vertex_color = mesh->has_vertex_property<Color>("v:color");
	Surface_mesh::Vertex_property<Color>  vcolor;
	if (has_vertex_color) vcolor = mesh->get_vertex_property<Color>("v:color");

	// setup vertex arrays    
	gl::glVertexPointer(points.data());
	gl::glNormalPointer(vnormals.data());
	if(has_vertex_color) gl::glColorPointer(vcolor.data());
	else glColor4dv(Vec4d(0.75,0.75,0.75,1.0));

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	if(has_vertex_color) glEnableClientState(GL_COLOR_ARRAY);
	glDrawElements(GL_TRIANGLES, (GLsizei)triangles.size(), GL_UNSIGNED_INT, &triangles[0]);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void SurfaceMeshRenderer::draw_flat(){
	Surface_mesh::Vertex_property<Point>  points   = mesh->vertex_property<Point>("v:point");
	Surface_mesh::Vertex_property<Point>  vnormals = mesh->vertex_property<Point>("v:normal");
	Surface_mesh::Face_property<Point>    fnormals = mesh->face_property<Point>("f:normal");
	Surface_mesh::Vertex_property<float>  vtex     = mesh->vertex_property<float>("v:tex1D", 0.0);

	bool has_face_color = mesh->has_face_property<Color>("f:color");
	Surface_mesh::Face_property<Color> fcolor = mesh->get_face_property<Color>("f:color");

	// setup vertex arrays
	gl::glVertexPointer(points.data());
	gl::glNormalPointer(vnormals.data());
	gl::glTexCoordPointer(vtex.data());    

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDepthRange(0.01, 1.0);

	Surface_mesh::Face_iterator fit, fend=mesh->faces_end();
	Surface_mesh::Vertex_around_face_circulator fvit, fvend;

	for (fit=mesh->faces_begin(); fit!=fend; ++fit)
	{
		// this will be slow, but we don't want to distinguish between
		// triangles, quads, and general polygons
		// immediate mode rendering is slow anyway...
		glBegin(GL_POLYGON); 
		if(has_face_color) gl::glColor(fcolor[fit]);
		gl::glNormal(fnormals[fit]);
		fvit = fvend = mesh->vertices(fit);
		do
		{
			gl::glVertex(points[fvit]);
		}
		while (++fvit != fvend);
		glEnd();
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void SurfaceMeshRenderer::draw_flatwire(){
	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT );
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1);
	draw_flat(); /// DrawFill<nm,cm,tm>(); /// < in meshlab
	glDisable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glColor3f(.3f,.3f,.3f);
	draw_wireframe(); /// DrawWire<nm,CMNone>(); /// < in meshlab
	glPopAttrib();
}

void SurfaceMeshRenderer::draw_wireframe(){
#if 0
	if(!mesh->has_vertex_property<Point>("v:point"))
		throw StarlabException("Impossible to proceed");

	/// Setup Vertex Array
	Surface_mesh::Vertex_property<Point> points = mesh->vertex_property<Point>("v:point");
	gl::glVertexPointer(points.data());
	glEnableClientState(GL_VERTEX_ARRAY);

	/// Render
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.0, 0.0);
	glDepthRange(0.0, 1.0);
	glDepthFunc(GL_LEQUAL);
	glDrawElements(GL_LINES, (GLsizei)edges.size(), GL_UNSIGNED_INT, &edges[0]);
	glDepthFunc(GL_LESS);

	/// Slower but allows color
#else
	Surface_mesh::Vertex_property<Point> points = mesh->vertex_property<Point>("v:point");

	Surface_mesh::Edge_property<Color> ecolor = mesh->get_edge_property<Color>("e:color");
	bool has_edge_color = mesh->has_edge_property<Color>("e:color");

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	Surface_mesh::Edge_iterator eit, eend=mesh->edges_end();
	for (eit=mesh->edges_begin(); eit!=eend; ++eit){
		Surface_mesh::Edge e = eit;
		Surface_mesh::Vertex v0 = mesh->vertex(eit,0);
		Surface_mesh::Vertex v1 = mesh->vertex(eit,1);

		if(has_edge_color)
			gl::glColor(ecolor[eit]); ///< Apply color
		else
			gl::glColor(Color(0,0,0));

		gl::glVertex(points[v0]);
		gl::glVertex(points[v1]);
	}
	glEnd();
	glEnable(GL_LIGHTING);
#endif
}

typedef Surface_mesh::Face_iterator FaceItr;
typedef std::pair<double, FaceItr> DepthFace;

bool depthSorter(DepthFace i, DepthFace j){ return (i.first < j.first); }

void SurfaceMeshRenderer::draw_transp_smooth(){

	Surface_mesh::Vertex_property<Point>  points = mesh->vertex_property<Point>("v:point");    
	Surface_mesh::Vertex_property<Point>  vnormals = mesh->vertex_property<Point>("v:normal");

	// Deal with color
	bool has_vertex_color = mesh->has_vertex_property<Color>("v:color");
	Surface_mesh::Vertex_property<Color>  vcolor;
	if (has_vertex_color) vcolor = mesh->get_vertex_property<Color>("v:color");

	Surface_mesh::Vertex_around_face_circulator fvit, fvend;

	/// Sort faces
	std::vector< DepthFace > depthvec;
	{
		triangles.clear();
		triangles.resize(mesh->n_faces());

		// Get current view transforms
		GLdouble projMatrix[16], modelMatrix[16];
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);

		// Temporary variables for projection
		double depth,x,y;
		GLint viewport[4] = {0, 100, 100, -100};

		/// Apply model transform and fill in depth & indexes
		Surface_mesh::Face_iterator fit, fend = mesh->faces_end();
		for (fit = mesh->faces_begin(); fit != fend; ++fit){

			// Compute face center
			Vector3 faceCenter(0,0,0);
			fvit = fvend = mesh->vertices(fit); int c = 0;
			do{ faceCenter += points[fvit]; c++; } while (++fvit != fvend);
			faceCenter /= c;

			// Project to get range 0 - 1.0
			gluProject(faceCenter.x(),faceCenter.y(),faceCenter.z(), modelMatrix, projMatrix, viewport,&x,&y,&depth);

			depthvec.push_back(DepthFace(depth, fit));
		}

		/// Sort depth 
		std::sort(depthvec.begin(), depthvec.end(), depthSorter);
	}

	/// Render
	{
		glShadeModel(GL_SMOOTH);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		{
            if(!has_vertex_color){
                Vec4d colorv(mesh->color);
                /// @todo minimum 10% transparency
                colorv[3] = qMin(.1,colorv[3]);
                glColor4dv(colorv);
            }
			glBegin(GL_TRIANGLES); 
			foreach(DepthFace f, depthvec)
			{
				FaceItr fit = f.second;
				fvit = fvend = mesh->vertices(fit);

				do{	
					if(has_vertex_color){
						// Fog like effect
						glColor4dv(Vec4d(vcolor[fvit][0],vcolor[fvit][1],vcolor[fvit][2], 1 - f.first));
					}

					gl::glNormal(vnormals[fvit]);
					gl::glVertex(points[fvit]); 
				} while (++fvit != fvend);
			}
			glEnd();
		}
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}
}
