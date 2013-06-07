#include "mode_controller.h"
Q_EXPORT_PLUGIN(mode_controller)

#include <QtOpenGL>
#include <QMouseEvent>
#include "StarlabDrawArea.h"
#include "Eigen/Geometry"

#include "StarlabGUIControllers.h"

void mode_controller::create(){
    manager = new ControllerManager( drawArea() );
    manager->add( new Controller( Vector3(  0,  0,  0) ) );
//    manager->add( new Controller( Vector3( .2, .2,  0) ) );
}

bool mode_controller::mouseMoveEvent(QMouseEvent* event){
    manager->mouseMoveEvent(event);
    return true;
}

bool mode_controller::mousePressEvent(QMouseEvent* event){
    manager->mousePressEvent(event);
    return true;
}

bool mode_controller::mouseReleaseEvent(QMouseEvent* event){
//    manager->mouseReleaseEvent(event);
    return true;
}

void mode_controller::decorate(){
    manager->draw();
}

void mode_controller::draw_with_names(){
    manager->draw_with_names();
}

