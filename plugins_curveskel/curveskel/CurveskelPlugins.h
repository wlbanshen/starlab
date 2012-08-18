#pragma once
#include "CurveskelModel.h"
#include "interfaces/InputOutputPlugin.h"
#include "interfaces/RenderPlugin.h"

/// Make this function valid only in this file
namespace{
    bool isA(Model* model){
        return qobject_cast<CurveskelModel*>(model);
    }
    CurveskelModel* safeCast(Model* model){
        CurveskelModel* _model = qobject_cast<CurveskelModel*>(model);
        if(!_model) throw StarlabException("Model is not a SurfaceMeshModel");
        return _model;
    }
}

class SkeletonInputOutputPlugin : public InputOutputPlugin{
private: 
    bool isApplicable(Model* model){ return isA(model); }
};


class CurveskelRenderPlugin : public RenderPlugin{
private:
    bool isApplicable(Model* model){ return isA(model); }
};
