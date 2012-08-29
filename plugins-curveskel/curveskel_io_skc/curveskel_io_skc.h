#pragma once
#include "CurveskelPlugins.h"
 
class curveskel_io_skc : public SkeletonInputOutputPlugin{
    Q_OBJECT
    Q_INTERFACES(InputOutputPlugin)
    
public:
    QString name(){ return "[Curveskel] Day's Skeleton Curve (*.skc)"; }
    Model* open(QString path);
    void save(CurveskelModel*, QString);
};
