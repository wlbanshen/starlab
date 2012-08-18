/// @todo this file should be split in a number of files inside the folder interfaces/
/// otherwise you will end up having to recompile all the surfacemeshplugins when it changes...

#pragma once
#include "interfaces/InputOutputPlugin.h"
#include "interfaces/DecoratePlugin.h"
#include "interfaces/FilterPlugin.h"

#include "SurfaceMeshModel.h"
#include "SurfaceMeshTypes.h"
using namespace SurfaceMeshTypes;

/// Make this function valid only in this file
namespace{
    bool isaSurfacemesh(Model* model){
        return qobject_cast<SurfaceMeshModel*>(model);
    }
    SurfaceMeshModel* safeCast(Model* model){
        SurfaceMeshModel* mesh = qobject_cast<SurfaceMeshModel*>(model);
        if(!mesh) throw StarlabException("Model is not a SurfaceMeshModel");
        return mesh;
    }
}

class SurfaceMeshFilterPlugin : public SelectionFilterPlugin{
public:
    virtual void applyFilter(SurfaceMeshModel* /*mesh*/, RichParameterSet*, StarlabDrawArea* /*drawArea*/) = 0;
    virtual void initParameters(SurfaceMeshModel* /*model*/, RichParameterSet* /*parameters*/, StarlabDrawArea* /*drawArea*/){}

private:
    bool isApplicable(Model* model) { 
        return isaSurfacemesh(model); 
    }
    void initParameters(Model* model, RichParameterSet* parameters, StarlabDrawArea* drawArea){
        initParameters(safeCast(model),parameters, drawArea); 
    }
    void applyFilter(Model* model, RichParameterSet* pars, StarlabDrawArea* drawArea){ 
        applyFilter(safeCast(model), pars, drawArea); 
    }
};


class SurfaceMeshDecoratePlugin : public DecoratePlugin{
public:
    virtual void decorate(SurfaceMeshModel* model, StarlabDrawArea* /*parent*/, QPainter* /*p*/) = 0;
private:
    bool isApplicable(Model* model) { return isaSurfacemesh(model); }
    void decorate(Model* model, StarlabDrawArea* parent, QPainter* p){ 
        return decorate(safeCast(model),parent,p); 
    }
};

class SurfaceMeshInputOutputPlugin : public InputOutputPlugin{
private: 
    bool isApplicable(Model* model){ return (bool) qobject_cast<SurfaceMeshModel*>(model); }
    void save(QString path, Model* model){ save(path,safeCast(model)); }    
public:
    virtual void save(QString /*path*/, SurfaceMeshModel* model) = 0;
};
