#include "SurfaceMeshHelper.h"
#include "manipulatedFrame.h"
using namespace qglviewer;

class ARAPDeformerHandle: public ManipulatedFrame{
    Q_OBJECT

public:
    ARAPDeformerHandle(const Vector3 & start){
        this->startPos = start;
        this->setPosition(start.x(), start.y(), start.z());
    }

    Vector3 transform(const Vector3 & originalPos){
        Vector3 d = originalPos - startPos;
        Vec delta(d[0], d[1], d[2]);
        Vec rotatedDelta = this->rotation() * delta;
        Vec newPos = this->position() + rotatedDelta;
        return Vector3(newPos.x, newPos.y, newPos.z);
    }

private:
    Vector3 startPos;
};
