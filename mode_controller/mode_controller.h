#pragma once
#include "ModePlugin.h"
#include "StarlabMainWindow.h"

/// FW
class Octree;
class ControllerManager;

class mode_controller : public ModePlugin{
    Q_OBJECT
    Q_INTERFACES(ModePlugin)

    QIcon icon(){ return QIcon(":/icons/select_points.png"); }
    bool isApplicable(){ return true; }

private:
    ControllerManager* manager;
    
public:
    /// Functions part of the EditPlugin system
    void create();
    void destroy(){}
    void decorate();
    void draw_with_names();
    
    bool mouseReleaseEvent(QMouseEvent*);
    bool mousePressEvent(QMouseEvent*);
    bool mouseMoveEvent(QMouseEvent*);
};
