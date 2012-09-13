#include <QMouseEvent>

#include "surfacemesh_mode_arapdeform.h"

#include "StarlabDrawArea.h"
#include "float.h"
#include <qgl.h>

using namespace qglviewer;

void surfacemesh_mode_arapdeform::create(){
	update();
}

void surfacemesh_mode_arapdeform::update(){}

Q_EXPORT_PLUGIN(surfacemesh_mode_arapdeform)
