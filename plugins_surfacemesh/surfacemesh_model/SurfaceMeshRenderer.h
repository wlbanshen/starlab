#pragma once
#include <QObject>
#include <QAction>
#include "ModelRenderer.h"
#include "SurfaceMeshModel.h"

/// @todo: attempt to merge draw_wireframe with draw_wireframe_color?
class SurfaceMeshRenderer : public ModelRenderer{
    Q_OBJECT
      
private:
    SurfaceMeshModel* mesh;
    
    /// @{ 
    private:
        QAction* _mode_cloud;
        QAction* _mode_flatshaded; 
        QAction* _mode_smoothshaded;
        QAction* _mode_flatwire;
        QAction* _mode_wireframe;
		QAction* _mode_transp_smooth;
    /// @}

private:
    std::vector<unsigned int>  triangles; ///< index array for buffered OpenGL rendering 
    std::vector<unsigned int>  edges;     ///< index array for buffered OpenGL rendering

	bool isReady;

public:
    SurfaceMeshRenderer();
    void setup(Model *model, QGLWidget *widget, QAction *shader);
    void init();
    void render();

public:
    void draw_points();
    void draw_smooth();
    void draw_flat();
    void draw_flatwire();
    void draw_wireframe();
	void draw_transp_smooth();
};
