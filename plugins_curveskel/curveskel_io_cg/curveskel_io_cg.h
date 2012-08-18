#pragma once
#include "CurveskelPlugins.h"
 
class curveskel_io_cg : public SkeletonInputOutputPlugin{
    Q_OBJECT
    Q_INTERFACES(InputOutputPlugin)
    
    QString name(){ return "[Curveskel] Curve Graph (*.cg)"; }
    Model* open(QString path);
    void save(QString, Model*);
};
