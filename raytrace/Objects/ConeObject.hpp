#include "BaseObject.hpp"
class ConeObject : public BaseObject {
    virtual bool testForIntersections(
        const qbRT::Ray &t_ray, 
        Vector3 &o_intersectionPoint, 
        Vector3 &o_localNormal,
        Vector3 &o_color
    ) const override;
    // get UV coordinates from an intersection
    virtual Vector3 getUVCoordinates(const Vector3 &t_intersectionPoint) const;
};