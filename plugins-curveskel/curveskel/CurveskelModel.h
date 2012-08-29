#pragma once

#include <QDebug>
#include <QString>

#include "global.h"
#include "Model.h"
#include "CurveskelTypes.h"

/// @{ Forward declaration of helpers defined in helper/...
///    This reduces clutter of this class header
class CurveskelForEachVertexHelper;
class CurveskelForEachEdgeHelper;
/// @}

using namespace CurveskelTypes;

class EXPORT CurveskelModel : public Model, public CurveskelTypes::MyWingedMesh{
    Q_OBJECT
    Q_INTERFACES(Model)
   
public:
    CurveskelModel(QString path, QString name=QString());
    void updateBoundingBox();
    
    /// @{ Qt foreach helpers
    public:
        CurveskelForEachVertexHelper vertices();
        CurveskelForEachEdgeHelper edges();
    /// @}
};
