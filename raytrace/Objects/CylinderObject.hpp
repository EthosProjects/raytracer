#include "BaseObject.hpp"
class CylinderObject : public BaseObject {
    virtual bool testForIntersections(
        const qbRT::Ray &t_ray, 
        Vector3 &o_intersectionPoint, 
        Vector3 &o_localNormal,
        Vector3 &o_color
    )  override;
};